#include "stdafx.h"
#include "ClientConnect.h"
#include"parsedata.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbclientpresenter.h"

ClientConnection::ClientConnection(QObject *parent)
  : QObject(parent)
  , m_client(nullptr)
  , m_user()
  , m_db()
  , m_idDialog(0)
  , m_idFriend(0)
{

}

ClientConnection::~ClientConnection()
{
}

void ClientConnection::slotConnection(const QString& hostName,int port)
{
    m_client = new QSslSocket(this);

    if(m_client == nullptr)
    {
        qDebug()<<"Start client: m_client=nullptr";
        return ;
    }

    qDebug() << hostName + ' ' + QString::number(port);

    m_client->setLocalCertificate("../../secure/client.crt");
    m_client->setPrivateKey("../../secure/client.key",QSsl::Rsa,QSsl::Pem,"2048");

    m_client->addCaCertificates("../../secure/sslserver.pem");
    m_client->connectToHostEncrypted(hostName, port);
    m_client->setProtocol(QSsl::TlsV1_2);

    connect(m_client,&QSslSocket::encrypted,this, &ClientConnection::slotEncrypted);
    connect(m_client,&QSslSocket::readyRead,this,&ClientConnection::slotReadyRead);
    connect(m_client, SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslError(QList<QSslError>)) );
    connect(m_client,&QSslSocket::disconnected, this, &ClientConnection::slotDisconnect);


}

 void ClientConnection::sslError( QList<QSslError> errors )
 {
     QString erroStr = "";
     foreach (const QSslError &e, errors)
         erroStr.append(e.errorString()).append("\n");

    qDebug() << erroStr;

     m_client->ignoreSslErrors();
 }

void ClientConnection::slotDisconnect()
{
    m_client->disconnectFromHost();
}


void ClientConnection::slotEncrypted()
{
    qDebug()<<"Mode is encryped";
}



 void  ClientConnection::slotReadyRead()
 {
     int idSender = -1;

     QString message = m_client->readAll();    // Read message
     qDebug()<<"Client got-> " << message;

     QString time=StringHandlNamespace::variable(message);

     qDebug()<<"Time: "<<time;
         switch((StringHandlNamespace::variable(message)).toInt())
         {

         case Error:

             qDebug() << "Error... " << message;

             emit signalSendRespond(QString::number(Error) + ' ' + message);

             break;

         case Connection:

            qDebug()<<message;

            emit signalSendRespond(QString::number(Connection));

                 break;

         case Registration:

             qDebug()<<"Success registration";

             // create db
             m_db.createDB("Client_"+m_user.getLogin()+".db");

             // insert user into tables session
             m_db.insertUser(m_user);

             m_user.setID(StringHandlNamespace::variable(message).toInt());

             qDebug()<<"My ID-> "<<m_user.getID();

             emit signalSendRespond(QString::number(Registration));


                 break;

             case Authorization:

             qDebug()<<"Success authorization";

             // create db
             m_db.createDB("Client_"+m_user.getLogin()+".db");

             m_db.insertUser(m_user);

             m_user.setID(StringHandlNamespace::variable(message).toInt());

             qDebug()<<"My ID-> "<<m_user.getID();

             // get lists of clients who are online
             sendToServer(QString::number(GetListOfFriends));

             emit signalSendRespond(QString::number(Authorization));

                 break;

             case Message:

             idSender = (StringHandlNamespace::variable(message)).toInt();

                qDebug() << message;
                 m_idDialog = m_db.searchIdDialog(idSender,m_user.getID());

                 if(m_idDialog < 0 )
                 {
                     qDebug() << "The dialog dosn't exist";
                     m_db.insertDialog(idSender,m_user.getID());
                 }
                 else
                    m_db.insertMessage(time+' '+message,m_idDialog);

                 emit signalSendMessage();

                 break;

             case File:
                 break;

         case GetListOfFriends:

             qDebug() << "GetNewList";

             emit signalSendRespond(QString::number(GetListOfFriends) + ' ' + message);


             break;
    }
 }

 void ClientConnection::sendToServer(const QString& message)
 {
     if(m_client != nullptr)
    {
         qDebug() << "Client sent-> " << QTime::currentTime().toString() + ' ' + message;
         m_client->write((QTime::currentTime().toString() + ' ' + message).toLocal8Bit());
     }
     else
         qDebug() << "SendToServer: m_client=nullptr";

 }

 void ClientConnection::slotRegistration(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Registration) + ' ' + login + ' ' + pass);


 }

 void ClientConnection::slotGetListFriend()
 {
     // get lists of clients who are online
     sendToServer(QString::number(GetListOfFriends));
 }

 void ClientConnection::slotChoiceFriend(const int& id)
 {
     m_idFriend = id;

     qDebug()<<"My id-> " << m_user.getID() << "Friend id-> " << m_idFriend;

     // search dialog
     int idDialog = m_db.searchIdDialog(m_user.getID(), m_idFriend);

     if(idDialog < 0)
     {
         qDebug() << "The dialog doesn't exist";
         // add dialog
         m_db.insertDialog(m_user.getID(), m_idFriend);

     }
     else
         qDebug()<<"The dialog exists";
 }


  void ClientConnection::showDialog()
  {
    QQueue<QString> q = m_db.showDialog(0);

    for(int i = 0 ; i<q.size(); i++)
    {
        qDebug() << q[i];
    }
  }



 void ClientConnection::slotAuthorization(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Authorization) + ' ' + login + ' ' + pass);
 }

 void ClientConnection::sendMessage(const QString& mess)
 {
    sendToServer(QString::number(Message) + ' ' + QString::number(m_user.getID()) + ' ' + QString::number(m_idFriend) + ' ' + mess);

 }




 void ClientConnection::sendFile(const QString& filename)
 {

     QFile file(filename);

     if(!file.open(QIODevice::ReadOnly))
     {
         qDebug() << "Error";
     }
     // create inByteArray for saving file
     QByteArray inByteArray=file.readAll();
     qDebug()<<inByteArray;


     file.close();

     m_db.insertFile(filename,inByteArray);



 }


void ClientConnection::getFile()
{
    int i=1;
    QFile file;
    QVariantList list= m_db.searchFile(i);
    if(list.empty())
    {
        qDebug()<<"Not File";
        return;
    }
    else {
           qDebug()<<list[0].toString();
           qDebug()<<list[1].toByteArray();

           file.setFileName(list[0].toString());

           if(!file.open(QIODevice::WriteOnly))
           {
               qDebug() << "Error";
           }
           else
           {
               file.write(list[1].toByteArray());
           }

    }

     file.close();
}


