#include "stdafx.h"

#include "mythread.h"
#include "data.h"

MyThread::MyThread(qintptr ID, DB::DBServerPresenter* db,QHash<int,QSslSocket*>* hash, QObject *parent)
    : QThread(parent)
    , m_mutexDB()
    , m_mutexHashTab()
    , m_db(db)
    , m_hash(hash)
    , m_sslClient(nullptr)
{
    this->m_socketDescriptor = ID;
}


void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    m_sslClient = std::shared_ptr<QSslSocket>(new QSslSocket());

    // set the ID
    if(!m_sslClient->setSocketDescriptor(this->m_socketDescriptor))
    {
        qDebug()<<"Error with descriptor";
        emit error(m_sslClient->error());
        return;
    }

    QFile certificateFile("../../secure/client.crt");

    if (!certificateFile.open(QIODevice::ReadOnly))
      return;
        // throw std::exception("Error: certificate doesn't open");

    QSslCertificate cert(certificateFile.readAll());

    certificateFile.close();

    m_sslClient->addCaCertificate(cert);

    m_sslClient->setLocalCertificate("../../secure/sslserver.pem");

    m_sslClient->setPrivateKey("../../secure/sslserver.key",QSsl::Rsa, QSsl::Pem,"password");
    m_sslClient->setProtocol(QSsl::TlsV1_2);
    m_sslClient->startServerEncryption();

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead, Qt::DirectConnection);
    connect(m_sslClient.get(), &QSslSocket::disconnected, this, &MyThread::slotDisconnect);
  //  connect( m_sslClient, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslError(QList<QSslError>)),Qt::DirectConnection);

    sendToClient(m_sslClient.get(),QString::number(Connection)+" Hello Client");

    exec();
}


bool MyThread::sendToClient(QSslSocket* pSocket,const QString& message)
{
    if (pSocket != nullptr)
    {
        qDebug()<<"Server sent-> "<< message;
        pSocket->write(message.toLocal8Bit());
        return true;
    }
    else
    {
        qDebug() << "Invalid socket ptr";
        return false;
    }
}

void MyThread::slotReadyRead()
{

    if(m_sslClient==nullptr)
    {
        qDebug()<<"Read: m_sslClient=nullptr";      
        return;
    }

    QString mess = m_sslClient->readAll();    // Read message
    qDebug() << "Client has sent -" << mess;

    switch ((Data::variable(mess)).toInt())
    {

    case Error:
        qDebug()<<"Upss..";
        break;
    case Message:

        qDebug()<<"MESSAGE\n";

        message(mess);
    break;

    case Registration:
        qDebug()<<"Registration\n";

        registration(mess);

    break;

    case Authorization:
        qDebug()<<"Authorization\n";
        authorization(mess);
    break;

    case GetListOfFriends:

        qDebug()<<"GetNewList";
        sendList();
        break;

    default:
        break;
    }

}


void MyThread::registration(QString& req)
{
    int id = 0;
    QString log = Data::variable(req);
    QString pass = Data::variable(req);

    // insert user into db
    qDebug() << "User: " << log << ", " << pass;

    m_mutexDB.lock();

    if(!m_db->insertUser(User(log, pass)))
      {
        m_mutexDB.unlock();

        sendToClient(m_sslClient.get(), QString::number(Error) + " The user's already existed with that login");
        return;
      }

     m_mutexDB.unlock();

     id = m_db->searchID(log);

    if(id == 0)
    {
        qDebug() << "The id doesn't exist";
    }
    else
    {
         m_mutexHashTab.lock();

         qDebug() << "ID: " << id;
         m_hash->insert(id, m_sslClient.get());

         m_mutexHashTab.unlock();

        sendToClient(m_sslClient.get(), QString::number(Registration) + ' ' + QString::number(id));
    }
}

void MyThread::authorization(QString& req)
{
    QString log = Data::variable(req);
    QString pass = Data::variable(req);

    // search user into db
    qDebug() << "User: " << log << ", " << pass;

    User* us = m_db->searchUser(log);

    if(us==nullptr)
    {
        sendToClient(m_sslClient.get(), QString::number(Error) + " The user didn't exist with that login");
        return;
    }

    if(us->getPassword() != pass)
    {
         sendToClient(m_sslClient.get(), QString::number(Error) + " The wrong password");
         return;
    }

    if(m_hash->contains(us->getID()))
    {
         sendToClient(m_sslClient.get(),QString::number(Error) + " The account is already used");
         return;
    }

    m_mutexHashTab.lock();

    qDebug() << "ID: " << us->getID();
    m_hash->insert(us->getID(), m_sslClient.get());

    m_mutexHashTab.unlock();

    sendToClient(m_sslClient.get(), QString::number(Authorization) + " " + QString::number(us->getID()));
}


void MyThread::sendList()
{
    QString login;
    QHash<int,QString> hashClients;
    QHash<int,QSslSocket*>::iterator iter;

      iter=m_hash->begin();
      while(iter!=m_hash->end())
      {

         login = m_db->searchLogin(iter.key());
          if(login != "")
          {
              hashClients.insert(iter.key(),login);
              qDebug()<<"id "<<iter.key()<<' '+login;
          }
          ++iter;
      }

     qDebug()<<"Vector: "+Data::concatenationHash(hashClients);
     sendToClient(m_sslClient.get(),QString::number(GetListOfFriends)+' '+Data::concatenationHash(hashClients));
}

void MyThread::message(QString& str)
{
    int myID = Data::variable(str).toInt();
    int friendID = Data::variable(str).toInt();
    bool flag;

    qDebug()<<"myID="<<myID<<" friendID"<<friendID;

    flag = sendToClient((*m_hash)[friendID], QString::number(Message) + ' ' + QString::number(myID) + ' ' +QString::number(0) + ' ' + str);

    if(!flag)
    {
        sendToClient((*m_hash)[myID], QString::number(Error) + " The message doesn't send");
    }

}

void MyThread::slotDisconnect()
{
    m_mutexHashTab.lock();
    QHash<int,QSslSocket*>::iterator iter=m_hash->begin();

    qDebug()<<"Disconnect: size of hash="<<m_hash->size();
        while(iter!=m_hash->end())
        {
            if(iter.value()==m_sslClient.get())
            {
                qDebug()<<"Dissconect: id="<<iter.key();

                  m_hash->erase(iter);

                 qDebug()<<" Size of hash="<<m_hash->size();
                return;
            }
             ++iter;
        }

     m_mutexHashTab.unlock();

     m_sslClient->disconnect();
     m_sslClient->deleteLater();

     exit(0);
}
