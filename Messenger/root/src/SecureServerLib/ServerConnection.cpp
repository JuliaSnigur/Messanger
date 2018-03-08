#include "stdafx.h"

#include "ServerConnection.h"
#include"parsedata.h"

#include "SslServer.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"

ServerConnection::ServerConnection(QObject *parent) :
    QObject(parent)
  ,m_sslServer(nullptr)
  ,m_sslClient(nullptr)
  ,m_hash()
  ,m_db()
{

}


 void ServerConnection::start(int port)
 {
     m_sslServer=new SslServer(this);

     if(m_sslServer==nullptr)
     {
         qDebug()<<"Start server: m_sslServer=nullptr";
         return ;
     }

     //set sertificate and private key
     m_sslServer->setSslLocalCertificate("../../secure/sslserver.pem");
     m_sslServer->setSslPrivateKey("../../secure/sslserver.key",QSsl::Rsa, QSsl::Pem,"password");

     //set version TLS 2.1
     m_sslServer->setSslProtocol(QSsl::TlsV1_2);

     //start listening
     if (m_sslServer->listen(QHostAddress::Any, port))
     {
         qDebug() << "Now listening on:" << port;

          connect(m_sslServer, SIGNAL(newConnection()),SLOT(slotConnection()));

     }
     else
         qDebug() << "ERROR: could not bind to:" << port;


 }


 void ServerConnection::slotConnection()
 {
     qDebug() << "New connection";

     m_sslClient = dynamic_cast<QSslSocket*>(m_sslServer->nextPendingConnection());

     if(m_sslClient!=nullptr)
     {
          connect(m_sslClient, &QSslSocket::readyRead, this, &ServerConnection::slotReadyRead);
         connect(m_sslClient, &QSslSocket::disconnected,this, &ServerConnection::deleteLater);
         connect(m_sslClient,&QSslSocket::disconnected, this, &ServerConnection::slotDisconnect);

         sendToClient(m_sslClient,QString::number(Connection)+" Hello Client");
     }
     else
     {
         qDebug()<<"Connect: m_sslClient=nullptr";
     }
 }


 void ServerConnection::sendToClient(QSslSocket* pSocket,const QString& message)
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


  void ServerConnection::slotReadyRead()
  {
      m_sslClient = (QSslSocket*)sender();


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
      break;

      case GetNewList:

          qDebug()<<"GetNewList";
          sendList();
          break;

      default:
          break;
      }
  }


  void ServerConnection::registration(QString& req)
  {
      int id=0;
      QString log=StringHandlNamespace::variable(req), pass=StringHandlNamespace::variable(req);

      // insert user into db
      qDebug()<<"User: "<<log<<", "<<pass;

      if(!m_db.insertUser(User(log,pass)))
        {
          sendToClient(m_sslClient,QString::number(Error)+" The login is exist");
          return;
        }
       id=m_db.searchID(log);

      if(id<0)
      {
          qDebug()<<"The id doesn't exist";
      }
      else
      {
           qDebug()<<"ID: "<<id;
           m_hash.insert(id,m_sslClient);
          sendToClient(m_sslClient,QString::number(Registration)+" "+QString::number(id));
      }
  }

  void ServerConnection::authorization(QString& str)
  {

  }


  void ServerConnection::sendList()
  {
      QVector<int> vec;
      QHash<int,QSslSocket*>::iterator iter;

      if(m_hash.size()>1)
     {
        iter=m_hash.begin();
        while(iter!=m_hash.end())
        {
            vec.push_back(iter.key());
            ++iter;
        }
        qDebug()<<"Vector: "+StringHandlNamespace::concatenationVec(vec);
       sendToAllClients(QString::number(GetNewList)+' '+StringHandlNamespace::concatenationVec(vec));
      }
      else
        {
            qDebug()<<m_hash.size()<< " client";
            sendToAllClients(QString::number(Error)+" Just 1 connection");
        }

}


  void ServerConnection::message(QString& str)
  {
      // id friend
      int myID=StringHandlNamespace::variable(str).toInt();
      int friendID=StringHandlNamespace::variable(str).toInt();

      QString login=m_db.searchLogin(myID);

      if(login!="")
           sendToClient(m_hash[friendID],QString::number(Message)+' '+login+": "+str);
      else
          sendToClient(m_hash[myID],QString::number(Error)+" The message dosn't send");

  }


  void ServerConnection::slotDisconnect()
  {
      QHash<int,QSslSocket*>::iterator iter=m_hash.begin();

      qDebug()<<"Disconnect: size of hash="<<m_hash.size();

      if(m_hash.size()>0)
      {
          while(iter!=m_hash.end())
          {
              if(iter.value()==nullptr)
              {
                  qDebug()<<"Dissconect: id="<<iter.key();
                  m_hash.erase(iter);
                   qDebug()<<" Size of hash="<<m_hash.size();

                  return;
              }
               ++iter;
          }

           sendList();
      }

  }


  void ServerConnection::sendToAllClients( const QString& str)
  {
      QHash<int,QSslSocket*>::iterator iter=m_hash.begin();
      while(iter!=m_hash.end())
      {
           sendToClient(iter.value(),str);
            ++iter;
      }
  }



void ServerConnection::run()
{
    QHostAddress address = QHostAddress::Any;
    quint16 port = 22333;

    m_sslServer->setSslLocalCertificate("D:/Qt/SslProject/Server/sslserver.pem");
    m_sslServer->setSslPrivateKey("D:/Qt/SslProject/Server/sslserver.key");
    m_sslServer->setSslProtocol(QSsl::TlsV1SslV3);

    if (m_sslServer->listen(address, port))
        qDebug().nospace() << "Now listening on " << qPrintable(address.toString()) << ":" << port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;

    if (m_sslServer->waitForNewConnection(-1))    // Wait until a new connection is received, -1 means no timeout
    {
        qDebug() << "New connection";
        QSslSocket *sslSocket = dynamic_cast<QSslSocket*>(m_sslServer->nextPendingConnection());

        if (sslSocket->waitForReadyRead(5000))    // Wait until some data is received, 5000 ms timeout (-1 doesn't work here)
        {
            QByteArray message = sslSocket->readAll();    // Read message
            qDebug() << "Message:" << QString(message);

            sslSocket->disconnectFromHost();    // Disconnect
            sslSocket->waitForDisconnected();    // Wait until disconnected
            qDebug() << "Disconnected";
        }

        else
        {
            qDebug().nospace() << "ERROR: could not receive message (" << qPrintable(sslSocket->errorString()) << ")";
        }
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(m_sslServer->errorString()) << ")";
    }

  //  this->deleteLater();
    //QThread::currentThread()->quit();
    //qApp->exit();
}
