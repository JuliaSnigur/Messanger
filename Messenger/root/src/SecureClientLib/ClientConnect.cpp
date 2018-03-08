#include "stdafx.h"

#include "ClientConnect.h"
#include"parsedata.h"


ClientConnection::ClientConnection(QObject *parent) :
    QObject(parent)
{
}

ClientConnection::~ClientConnection(){}

void ClientConnection::start(const QString& hostName,int port)
{
    m_client=new QSslSocket(this);

    if(m_client==nullptr)
    {
        qDebug()<<"Start client: m_client=nullptr";
        return ;
    }
// sertificate includes private key ecryption
    m_client->addCaCertificates("../../secure/sslserver.pem");
    m_client->connectToHostEncrypted(hostName, port);

    connect(m_client,&QSslSocket::encrypted,this, &ClientConnection::slotEncrypted);
    connect(m_client,&QSslSocket::readyRead,this,&ClientConnection::slotReadyRead);
   // connect(m_client,&QSslSocket::sslErrors,this,&ClientExample::slotErrors);

}



void ClientConnection::slotEncrypted()
{
    qDebug()<<"Mode is encryped";
}

void ClientConnection::slotErrors(const QList<QSslError> &errors)
{
    QString errorStrings;
    foreach (QSslError error, errors)
    {
      errorStrings += error.errorString();
      if (error != errors.last())
      {
        errorStrings += '\n';
      }
    }
    qDebug()<<errorStrings;
}

 void  ClientConnection::slotReadyRead()
 {
     QString message = m_client->readAll();    // Read message
     qDebug()<<"Client got-> " << message;

     QString time=StringHandlNamespace::variable(message);

     qDebug()<<"Time: "<<time;
         switch((StringHandlNamespace::variable(message)).toInt())
         {

         case Error:
             qDebug()<<"Upss.. "<<message;
             break;

         case Connection:

                 qDebug()<<message;
            emit signalSendInfo();
                 break;

         case Registration:

             qDebug()<<"Success registration";

             // insert user into tables session
               emit signalInsertUserIntoTabSession();

             qDebug()<<"GetID";
             emit signalGetID(StringHandlNamespace::variable(message).toInt());

             // get lists of clients who are online
             sendToServer(QString::number(GetNewList));
                 break;

             case Authorization:
                 break;

             case Message:
             qDebug()<<message;

             emit signalSendMessage();
                 break;

             case File:
                 break;

         case GetNewList:
             qDebug()<<"GetNewList";
             emit signalGetListsClients(StringHandlNamespace::separateVec(message));
             break;
    }
 }

 void ClientConnection::sendToServer(const QString& message)
 {
     if(m_client!=nullptr)
    {
         qDebug()<<"Client sent-> "<< QTime::currentTime().toString()+' '+message;
         m_client->write((QTime::currentTime().toString()+' '+message).toLocal8Bit());
     }
     else
         qDebug()<<"SendToServer: m_client=nullptr";

 }

void ClientConnection::run()
{
    QString hostName = "127.0.0.1";    // DO NOT CHANGE THIS AS IT MUST MATCH THE FQDN OF THE CERTIFICATE (you MUST create your own certificate in order to change this)
    quint16 port = 22333;

    QSslSocket sslSocket;
    sslSocket.addCaCertificates("../../SslProject/sslserver.pem");
    sslSocket.connectToHostEncrypted(hostName, port);

    if (sslSocket.waitForEncrypted(-1))    // Wait until encrypted connection is established, -1 means no timeout
    {
        qDebug() << "Connected";
        sslSocket.write("Hello, World!");    // Send message to the server

        if (sslSocket.waitForBytesWritten(-1))    // Wait until message is sent (also makes QSslSocket flush the buffer)
            qDebug() << "Message sent";
        else
            qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";

        while (!sslSocket.waitForDisconnected())    // Wait until disconnected
            QThread::msleep(10);

        qDebug() << "Disconnected";
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
    }

   // this->deleteLater();
    //QThread::currentThread()->quit();
    //qApp->exit();
}
