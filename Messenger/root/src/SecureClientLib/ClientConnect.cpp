#include "stdafx.h"

#include "ClientConnect.h"
#include "data.h"

#include "user.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

Client::ClientConnection::ClientConnection(QObject *parent)
  : QObject(parent)
  , m_client(nullptr)
  , m_user()
  , m_db()
  , m_idDialog(0)
  , m_idFriend(0)
  , m_fileName("")
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
}

void Client::ClientConnection::slotConnection(const QString& hostName,int port)
{
    m_client = std::shared_ptr<QSslSocket>(new QSslSocket(this));

    if(m_client == nullptr)
    {
        qDebug() << "Start client: m_client=nullptr";
        emit signalSendRespond( "Don't connect to server" );
        return;
    }

    qDebug() << hostName + ' ' + QString::number(port);

    m_client->setLocalCertificate("../../secure/client.crt");
    m_client->setPrivateKey("../../secure/client.key",QSsl::Rsa,QSsl::Pem,"2048");
    m_client->addCaCertificates("../../secure/sslserver.pem");
    m_client->connectToHostEncrypted(hostName, port);
    m_client->setProtocol(QSsl::TlsV1_2);

    connect(m_client.get(),&QSslSocket::encrypted,this, &ClientConnection::slotEncrypted);
    connect(m_client.get(),&QSslSocket::readyRead,this,&ClientConnection::slotReadyRead);
    connect(m_client.get(), SIGNAL(sslErrors(QList<QSslError>)),this, SLOT(sslError(QList<QSslError>)) );
    connect(m_client.get(),&QSslSocket::disconnected, this, &ClientConnection::slotDisconnect);


}

 void Client::ClientConnection::sslError( QList<QSslError> errors )
 {
     QString erroStr = "";
     foreach (const QSslError &e, errors)
         erroStr.append(e.errorString()).append("\n");

    qDebug() << erroStr;

     m_client->ignoreSslErrors();
 }

void Client::ClientConnection::slotDisconnect()
{
    m_client->disconnectFromHost();
}


void Client::ClientConnection::slotEncrypted()
{
    qDebug() << "Mode is encryped";
}



 void  Client::ClientConnection::slotReadyRead()
 {
     int idSender = -1;
     int idFile = 0;
     QString time;

     QString message = m_client->readAll();    // Read message
     qDebug() << "Client got-> " << message;

         switch((Data::variable(message)).toInt())
         {

         case Error:
             qDebug() << "Error... " << message;
             emit signalSendRespond(QString::number(Error) + ' ' + message);
             break;

         case Connection:
            qDebug() << message;
            emit signalSendRespond(QString::number(Connection));
            break;

         case Registration:
             qDebug()<<"Success registration";
             m_db.createDB("Client_" + m_user.getLogin() + ".db");
             m_user.setID(Data::variable(message).toInt());
             qDebug()<<"My ID-> "<<m_user.getID();
             emit signalSendRespond(QString::number(Registration));
             break;

         case Authorization:
             qDebug()<<"Success authorization";
             m_db.createDB("Client_" + m_user.getLogin() + ".db");
             m_user.setID(Data::variable(message).toInt());
             qDebug()<<"My ID-> "<<m_user.getID();
             emit signalSendRespond(QString::number(Authorization));
             break;

         case Message:
            //  key, idFriend, idFile, time, mess
            idSender = (Data::variable(message)).toInt();
            idFile = (Data::variable(message)).toInt();
            time = Data::variable(message);

            qDebug() << message;
            m_idDialog = m_db.searchIdDialog(idSender);

            if(m_idDialog < 0 )
            {
                qDebug() << "The dialog dosn't exist";
                m_db.insertDialog(idSender);
            }
            else
            {
                m_db.insertMessage(m_idDialog,Get,message,time);
            }
            // str = loginRecipeint, time, messange, idFile
            emit signalSendRespond(QString::number(Message) + ' ' + time + ' ' + message);
            break;

         case File:

             break;

         case GetListOfFriends:
             qDebug() << "GetNewList";
             emit signalSendRespond(QString::number(GetListOfFriends) + ' ' + message);
             m_hash=Data::separateHash(message);
             break;

    }
 }

 void Client::ClientConnection::sendToServer(const QString& message)
 {
     if(m_client != nullptr)
     {
         qDebug() << "Client sent-> " <<  message;
         m_client->write(message.toLocal8Bit());
     }
     else
         qDebug() << "SendToServer: m_client=nullptr";

 }



 //////////////////////////////////////////////////////

 void Client::ClientConnection::slotRegistration(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Registration) + ' ' + login + ' ' + pass);


 }

 void Client::ClientConnection::slotGetListFriend()
 {
     // get lists of clients who are online
    sendToServer(QString::number(GetListOfFriends));
 }


 void Client::ClientConnection::slotChoiceFriend(const QString& login)
 {

     m_idFriend = m_hash.key(login);

     qDebug()<<"My id-> " << m_user.getID() << "Friend id-> " << m_idFriend;

     // search dialog
     int idDialog = m_db.searchIdDialog(m_idFriend);

     if(idDialog < 0)
     {
         qDebug() << "The dialog doesn't exist";
         // add dialog
         m_db.insertDialog(m_idFriend);

     }
     else
     {
         qDebug()<<"The dialog exists";

         QQueue<QString> q = m_db.showDialog(idDialog);

         for(int i = 0 ; i<q.size(); i++)
         {
              qDebug() << q[i];
         }

         emit signalSendDialog(q);


     }
     emit signalSendRespond(QString::number(GetFriend));


 }


 void Client::ClientConnection::slotAuthorization(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);

    sendToServer(QString::number(Authorization) + ' ' + login + ' ' + pass);
 }


 // format: time, message
 void Client::ClientConnection::slotSendMessage(const QString& message)
 {
     QString mess = message;
     QString time = Data::variable(mess);

     m_idDialog = m_db.searchIdDialog(m_idFriend);

     if(m_idDialog < 0 )
     {
         qDebug() << "The dialog dosn't exist";
         m_db.insertDialog(m_idFriend);
         m_idDialog = m_db.searchIdDialog(m_idFriend);
     }
         m_db.insertMessage(m_idDialog, Send, mess, time);

     if(m_idFriend != m_user.getID())
     {
         sendToServer(QString::number(Message) + ' ' + QString::number(m_user.getID()) + ' ' + QString::number(m_idFriend) + ' ' + message);
     }
 }


 void Client::ClientConnection::slotSendFile(const QString& fileName)
 {

     /*m_fileName = fileName;
     QFile file = QFile(fileName);

     if(file.open(QFile::ReadOnly))
     {
         qDebug()<<file.size();
        if(m_client)
        {
            m_client->write((QString::number(File) + ' ' + fileName + ' ' + QString::number(file.size())).toLatin1());
        }
        else
        {
            qDebug()<<"Error with sending file: m_client=nullptr";
        }
     }
     else
     {
       qDebug()<<"File not can open for read";
       return;
     }
     */
 }


 void Client::ClientConnection::sendFile(const QString& filename)
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


void Client::ClientConnection::getFile()
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


