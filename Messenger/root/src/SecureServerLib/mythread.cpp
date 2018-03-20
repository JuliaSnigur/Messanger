#include "stdafx.h"

#include "mythread.h"
#include "data.h"

Server::MyThread::MyThread(qintptr ID, std::shared_ptr<DB::DBServerPresenter> db,std::shared_ptr<QHash<int,QSslSocket*>> hash, QObject *parent)
    : QThread(parent)
    , m_mutexDB()
    , m_mutexHashTab()
    , m_sslClient(nullptr)
    , m_file()
    , m_sizeReceiveFile(0)
{
    this->m_socketDescriptor = ID;
    m_db = db;
    m_hash = hash;
}

Server::MyThread::~MyThread(){}

void Server::MyThread::run()
{
    qDebug() << " Thread started";

    m_sslClient = std::shared_ptr<QSslSocket>(new QSslSocket());

    if(!m_sslClient->setSocketDescriptor(this->m_socketDescriptor))
    {
        qDebug()<<"Error with descriptor";
        emit error(m_sslClient->error());
        return;
    }

    QFile certificateFile("../../secure/client.crt");
    if (!certificateFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Error: certificate doesn't open";
        return;
    }
    QSslCertificate cert(certificateFile.readAll());
    certificateFile.close();

    m_sslClient->addCaCertificate(cert);
    m_sslClient->setLocalCertificate("../../secure/sslserver.pem");
    m_sslClient->setPrivateKey("../../secure/sslserver.key", QSsl::Rsa, QSsl::Pem, "password");
    m_sslClient->setProtocol(QSsl::TlsV1_2);
    m_sslClient->startServerEncryption();

    connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead, Qt::DirectConnection);
    connect(m_sslClient.get(), &QSslSocket::disconnected, this, &MyThread::slotDisconnect);

    sendToClient(m_sslClient.get(), QString::number(Connection) + " Hello Client");

    exec();
}


bool Server::MyThread::sendToClient(QSslSocket* pSocket, const QString& message)
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

void Server::MyThread::slotReadyRead()
{
    QString fileName;

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

    case File:
        qDebug()<<"SendFile";
        fileName = Data::variable(mess);
        m_sizeReceiveFile = Data::variable(mess).toULong();
        receiveFile(fileName);
        break;

    default:
        break;
    }

}


void Server::MyThread::registration(QString& req)
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

void Server::MyThread::authorization(QString& req)
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


void Server::MyThread::sendList()
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

void Server::MyThread::message(QString& str)
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

void Server::MyThread::receiveFile(const QString& fileName)
{
    // путь сохранения файла
    m_file.setFileName(fileName);
    m_file.open(QIODevice::WriteOnly|QIODevice::Append);

    sendToClient(m_sslClient.get(), QString::number(File));

    disconnect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead);
    connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReceiveFile);
}

void Server::MyThread::slotReceiveFile()
{
    static ulong sizeReceivedData;

    QByteArray buff = m_sslClient->readAll();
    quint64 size =  m_file.write(buff);
    qDebug()<<"Write: "<<size;
    sizeReceivedData += size;

    if(sizeReceivedData == m_sizeReceiveFile)
    {
      m_file.close();

      m_sizeReceiveFile = 0;
      sizeReceivedData = 0;
      qDebug() << "Finished";

      disconnect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReceiveFile);
      connect(m_sslClient.get(), &QSslSocket::readyRead, this, &MyThread::slotReadyRead);
    }
}


void Server::MyThread::slotDisconnect()
{
    m_mutexHashTab.lock();
    QHash<int,QSslSocket*>::iterator iter=m_hash->begin();

    qDebug()<<"Disconnect: size of hash="<<m_hash->size();
        while(iter != m_hash->end())
        {
            if(iter.value() == m_sslClient.get())
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
