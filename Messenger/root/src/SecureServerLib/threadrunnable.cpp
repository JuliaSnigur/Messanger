#include"stdafx.h"
#include "threadrunnable.h"



#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"


#include"parsedata.h"

 QHash<int,QSslSocket*> ThreadRunnable::m_hash;
 DBServerPresenter ThreadRunnable::m_db ;


ThreadRunnable::ThreadRunnable(qintptr socketDescriptor,QObject* obj)
    :QObject(obj)
    ,m_mutexDB()
    ,m_mutexHashTab()
    ,m_socketDescriptor(socketDescriptor)
{
}




ThreadRunnable::~ThreadRunnable(){}


void ThreadRunnable::run()
{
    m_sslClient=new QSslSocket(this);

    if( m_sslClient->setSocketDescriptor(m_socketDescriptor))
    {

        // process handshake
        m_sslClient->setLocalCertificate("../../secure/sslserver.pem");
        m_sslClient->setPrivateKey("../../secure/sslserver.key",QSsl::Rsa, QSsl::Pem,"password");
        m_sslClient->setProtocol(QSsl::TlsV1_2);
        m_sslClient->startServerEncryption();

        connect(m_sslClient, SIGNAL(readyRead()),this, SLOT(slotReadyRead()),Qt::DirectConnection);
        connect(m_sslClient,SIGNAL(disconnected()),this, SLOT(slotDisconnect()),Qt::DirectConnection);
        connect( m_sslClient, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslError(QList<QSslError>)),Qt::DirectConnection);
        qDebug()<<"The thread started";

        qDebug()<<"Encryped";

    }
     else
    {
        qDebug() << "Error in socketDescriptor";

    }

    sendToClient(m_sslClient,QString::number(Connection)+" Hello Client");
}

void ThreadRunnable::slotSslError(QList<QSslError> errors)
{
    QString erroStr="";
    foreach (const QSslError &e, errors)
        erroStr.append(e.errorString()).append("\n");

   qDebug()<<erroStr;

    m_sslClient->ignoreSslErrors();
}

void ThreadRunnable::sendToClient(QSslSocket* pSocket,const QString& message)
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


 void ThreadRunnable::slotReadyRead()
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


 void ThreadRunnable::registration(QString& req)
 {


     int id=0;
     QString log=StringHandlNamespace::variable(req), pass=StringHandlNamespace::variable(req);

     // insert user into db
     qDebug()<<"User: "<<log<<", "<<pass;

     m_mutexDB.lock();

     if(!m_db.insertUser(User(log,pass)))
       {
         sendToClient(m_sslClient,QString::number(Error)+" The login is exist");
         return;
       }
      id=m_db.searchID(log);

      m_mutexDB.unlock();

     if(id<0)
     {
         qDebug()<<"The id doesn't exist";
     }
     else
     {
          qDebug()<<"ID: "<<id;

          m_mutexHashTab.lock();

          m_hash.insert(id,m_sslClient);

          m_mutexHashTab.unlock();

         sendToClient(m_sslClient,QString::number(Registration)+" "+QString::number(id));
     }


 }

 void ThreadRunnable::authorization(QString& str)
 {
 }


 void ThreadRunnable::sendList()
 {
     QVector<int> vec;
     QHash<int,QSslSocket*>::iterator iter;

     m_mutexHashTab.lock();

     if(m_hash.size()>1)
    {
       iter=m_hash.begin();
       while(iter!=m_hash.end())
       {
           vec.push_back(iter.key());
           ++iter;
       }
       qDebug()<<"Vector: "+StringHandlNamespace::concatenationVec(vec);
      sendToClient(m_sslClient,QString::number(GetNewList)+' '+StringHandlNamespace::concatenationVec(vec));
     }
     else
       {
           qDebug()<<m_hash.size()<< " client";
          sendToClient(m_sslClient,QString::number(Error)+" Just 1 connection");
       }

     m_mutexHashTab.unlock();

}


 void ThreadRunnable::message(QString& str)
 {
     // id friend
     int myID=StringHandlNamespace::variable(str).toInt();
     int friendID=StringHandlNamespace::variable(str).toInt();

     m_mutexDB.lock();

     QString login=m_db.searchLogin(myID);


     m_mutexDB.unlock();

     m_mutexHashTab.lock();

     if(login!="")
          sendToClient(m_hash[friendID],QString::number(Message)+' '+login+": "+str);
     else
         sendToClient(m_hash[myID],QString::number(Error)+" The message dosn't send");

     m_mutexHashTab.unlock();

 }


 void ThreadRunnable::slotDisconnect()
 {
    m_sslClient = dynamic_cast<QSslSocket*>(sender());

    m_mutexHashTab.lock();

    QHash<int,QSslSocket*>::iterator iter=m_hash.begin();
    while(iter!=m_hash.end())
    {
        if(iter.value()==m_sslClient)
        {
           m_sslClient->disconnect();
           m_sslClient->deleteLater();

           qDebug()<<"Dissconect: id="<<iter.key();

           m_hash.erase(iter);


             qDebug()<<" Size of hash="<<m_hash.size();
            return;
        }
         ++iter;
    }

    m_mutexHashTab.unlock();


}



