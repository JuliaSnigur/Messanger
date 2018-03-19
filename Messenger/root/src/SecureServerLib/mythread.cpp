#include"stdafx.h"
#include "mythread.h"

#include"parsedata.h"

MyThread::MyThread(qintptr ID,DBServerPresenter* db,QHash<int,QSslSocket*>* hash, QObject *parent)
    :QThread(parent)
    ,m_mutexDB()
    ,m_mutexHashTab()
    ,m_db(db)
    ,m_hash(hash)
    , m_sslClient(nullptr)
{
    this->m_socketDescriptor = ID;
}

MyThread::~MyThread()
{
}


void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    m_sslClient = new QSslSocket();

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

    connect(m_sslClient, &QSslSocket::readyRead, this, &MyThread::slotReadyRead, Qt::DirectConnection);
    connect(m_sslClient, &QSslSocket::disconnected, this, &MyThread::slotDisconnect);
  //  connect( m_sslClient, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslError(QList<QSslError>)),Qt::DirectConnection);

    sendToClient(m_sslClient,QString::number(Connection)+" Hello Client");

    exec();
}


void MyThread::sendToClient(QSslSocket* pSocket,const QString& message)
{
    if (pSocket != nullptr)
    {
        qDebug()<<"Server sent-> "<< QTime::currentTime().toString()+' '+message;
        pSocket->write( (QTime::currentTime().toString()+' '+message).toLocal8Bit());
    }
    else
    {
        qDebug() << "Invalid socket ptr";
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

    QString time=StringHandlNamespace::variable(mess);
    qDebug()<<"Time: "<<time;

    switch ((StringHandlNamespace::variable(mess)).toInt())
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
    int id=0;
    QString log=StringHandlNamespace::variable(req), pass=StringHandlNamespace::variable(req);

    // insert user into db
    qDebug()<<"User: "<<log<<", "<<pass;

    m_mutexDB.lock();

    if(!m_db->insertUser(User(log,pass)))
      {
        m_mutexDB.unlock();
        sendToClient(m_sslClient,QString::number(Error)+" The user's already existed with that login");
        return;
      }
     id=m_db->searchID(log);


     m_mutexDB.unlock();

    if(id<0)
    {
        qDebug()<<"The id doesn't exist";
    }
    else
    {
         m_mutexHashTab.lock();

         qDebug()<<"ID: "<<id;
         m_hash->insert(id,m_sslClient);

         m_mutexHashTab.unlock();

        sendToClient(m_sslClient,QString::number(Registration)+" "+QString::number(id));
    }
}

void MyThread::authorization(QString& req)
{
    int id=0;
    QString log=StringHandlNamespace::variable(req), pass=StringHandlNamespace::variable(req);

    // search user into db
    qDebug()<<"User: "<<log<<", "<<pass;

    User us=m_db->searchUser(log);

    if(us.getLogin()!="")
    {
        // compare passwords
        if(us.getPassword()==pass)
        {

            m_mutexHashTab.lock();

            qDebug()<<"ID: "<<id;

            // вставить проверку, если пользователь уже зашел под таким ником в систему
            m_hash->insert(id,m_sslClient);

            m_mutexHashTab.unlock();


             sendToClient(m_sslClient,QString::number(Authorization)+" "+QString::number(id));
        }
        else
        {
              sendToClient(m_sslClient,QString::number(Error)+" The wrong password");
        }
    }
    else
    {
        sendToClient(m_sslClient,QString::number(Error)+" The user didn't exist with that login");
    }

}


void MyThread::sendList()
{
    QString login;
    QHash<int,QString> hashClients;
    QHash<int,QSslSocket*>::iterator iter;

    if(m_hash->size()>1)
   {
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

     qDebug()<<"Vector: "+StringHandlNamespace::concatenationHash(hashClients);
     sendToClient(m_sslClient,QString::number(GetListOfFriends)+' '+StringHandlNamespace::concatenationHash(hashClients));
    }
    else
      {
          qDebug()<<m_hash->size()<< " client";
          sendToClient(m_sslClient,QString::number(Error)+" Just 1 connection");
      }


}


void MyThread::message(QString& str)
{
    // id friend
    int myID=StringHandlNamespace::variable(str).toInt();
    int friendID=StringHandlNamespace::variable(str).toInt();

    qDebug()<<"myID="<<myID<<" friendID"<<friendID;


    QString login=m_db->searchLogin(myID);

    if(login!="")
         sendToClient((*m_hash)[friendID],QString::number(Message)+' '+QString::number(myID)+' '+login+": "+str);
    else
        sendToClient((*m_hash)[myID],QString::number(Error)+" The message doesn't send");
}


void MyThread::slotDisconnect()
{
    m_mutexHashTab.lock();
    QHash<int,QSslSocket*>::iterator iter=m_hash->begin();

    qDebug()<<"Disconnect: size of hash="<<m_hash->size();
        while(iter!=m_hash->end())
        {
            if(iter.value()==m_sslClient)
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
