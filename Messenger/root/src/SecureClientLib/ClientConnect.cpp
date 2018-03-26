#include <QTextCodec>
#include <QQueue>


#include "ClientConnect.h"
#include "DataLib/data.h"
#include "DataLib/user.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"
#include "filethread.h"

Client::ClientConnection::ClientConnection(QObject *parent)
  : QObject(parent)
  , m_client(nullptr)
  , m_user()
  , m_db()
  , m_idDialog(0)
  , m_idFriend(0)
  , m_thread(new FileThread(this))
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     m_certServer = "-----BEGIN CERTIFICATE-----"
             "MIID2zCCAsOgAwIBAgIJALw0xDUVwv68MA0GCSqGSIb3DQEBBQUAMIGDMQswCQYD"
             "VQQGEwJGUjEPMA0GA1UECAwGRnJhbmNlMQ8wDQYDVQQKDAZHdWlUZUsxHTAbBgNV"
             "BAsMFFF0LVNzbFNlcnZlci1FeGFtcGxlMRIwEAYDVQQDDAkxMjcuMC4wLjExHzAd"
             "BgkqhkiG9w0BCQEWEGFkbWluQGd1aXRlay5uZXQwHhcNMTQwODE2MTY1MjU1WhcN"
             "MjQwODEzMTY1MjU1WjCBgzELMAkGA1UEBhMCRlIxDzANBgNVBAgMBkZyYW5jZTEP"
             "MA0GA1UECgwGR3VpVGVLMR0wGwYDVQQLDBRRdC1Tc2xTZXJ2ZXItRXhhbXBsZTES"
             "MBAGA1UEAwwJMTI3LjAuMC4xMR8wHQYJKoZIhvcNAQkBFhBhZG1pbkBndWl0ZWsu"
             "bmV0MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAtZ1MV1GwNcL+c6zz"
             "8n/kII9sZZGUPXo3zj20wDd9SK51vWDhgXK9QTsKF7FSZIV4C2AMVb7za5GEn/c5"
             "ZWOvEavUR5AovHgFau2E/J3UOg/ys/fa4vWeOQWwCZvkjV3ikpYjFzS7lXoMxqj2"
             "/GkPV+x0zqBJdElJ7dVnI5FQWurVDofYrY/SDzC7x5DTpdeNf9nwxUGL7l7Zqzum"
             "cVQpxlOHHjXwVXcHOyt0ifrkFq6Ghmhz6hok+pxBnQ8Np+91ZqD9ePFh+aDeONjx"
             "776srmVAZEXq7737yxjwIbOnvDKhAe/isQ6uLO93XbLfMSqCQB8e6FotZW2vcDWH"
             "HCF7cQIDAQABo1AwTjAdBgNVHQ4EFgQU1UpcmMVlTsRSXkjPOvxdSdJ6P8EwHwYD"
             "VR0jBBgwFoAU1UpcmMVlTsRSXkjPOvxdSdJ6P8EwDAYDVR0TBAUwAwEB/zANBgkq"
             "hkiG9w0BAQUFAAOCAQEABXl/seUVFqrVIo8o4aIC19SnQVgEwKaRLetxBVyFY1Jg"
             "GOadUayRf4mK3lAQFKghGQYNeI33SWM8lNnAILJiJTGRKrodXQuEFbjFD4CF/vTg"
             "WtjS7BQR3KscLjlDwgK5tw+jvYmCVcBJwV6uM+NyeZOdz8QEi7h7vD9dqpp53xB7"
             "PNyHHBLEyUGCTiKV/TbeoQFrdQWQ+LXczNaBUX2imtPDixikaqr4mHRX7YTpH2WB"
             "VQNvID9efhMtDnTotI3puNwqRLXK8LEB6mbj27lPik1Mx7r81zvDAkkd+D/9oNF2"
             "7BppFrbxPgUCg6RV2MXinG1Njt6z25dV2AQUZro9vA=="
             "-----END CERTIFICATE-----";


     connect( m_thread.get(), &FileThread::signalError, this, &ClientConnection::slotError);
     connect(this, &ClientConnection::signalSendFileBlock,  m_thread.get(), &FileThread::sendFileBlock);
}

Client::ClientConnection::~ClientConnection()
{
    m_thread->exit(0);
}

void Client::ClientConnection::slotConnection(const QString& hostName,const int& port)
{
    m_client = std::shared_ptr<QSslSocket>(new QSslSocket(this));
    if(m_client == nullptr)
    {
        emit signalSendRespond(QString::number(Data::Info) + " Don't connect to server" );
        qDebug() << "Start client: m_client=nullptr";
        return;
    }
    qDebug() << hostName + ' ' + QString::number(port);
/*
    QSslCertificate certSever(m_certServer,QSsl::Pem);
    m_client->addCaCertificate(certSever);
    m_client->setProtocol(QSsl::TlsV1_2);
    m_client->connectToHostEncrypted(hostName, port);
*/

    m_client->addCaCertificates("../../secure/sslserver.pem");
    m_client->setProtocol(QSsl::TlsV1_2);
    m_client->connectToHostEncrypted(hostName, port);

if(!m_client->waitForConnected())
    {
        emit signalSendRespond(QString::number(Data::Info) + " Not connection. Try again" );
        return;
    }
    connect(m_client.get(), &QSslSocket::encrypted, this, &ClientConnection::slotEncrypted);
    connect(m_client.get(), &QSslSocket::readyRead, this, &ClientConnection::slotReadyRead);
    connect(m_client.get(), SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(sslError(QList<QSslError>)));
    connect(m_client.get(),&QSslSocket::disconnected, this, &ClientConnection::slotDisconnect);
}

 void Client::ClientConnection::sslError(QList<QSslError> errors)
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
    qDebug()<<"Disconnect";
    m_thread->deleteLater();
}

 void Client::ClientConnection::slotEncrypted()
{
    qDebug() << "Mode is encryped";
}

 void  Client::ClientConnection::slotReadyRead()
 {
     int idSender = 0;
     QString time = "";
     QString message = m_client->readAll();
     qDebug() << "Client got-> " << message;
     switch(variable(message).toInt())
     {
         case  Data::Info:
             qDebug() << "Error... " << message;
             emit signalSendRespond(QString::number(Data::Info) + ' ' + message);
             break;

         case  Data::Connection:
            qDebug() << message;
            emit signalSendRespond(QString::number(Data::Connection));
            break;

         case  Data::Registration:
             qDebug()<<"Success registration";
             m_db.createDB(m_user.getLogin() + ".db");
             m_user.setID(variable(message).toInt());
             qDebug()<<"My ID-> "<<m_user.getID();
             emit signalSendRespond(QString::number( Data::Registration));
             sendToServer(QString::number( Data::GetListOfFriends));
             break;

         case  Data::Authorization:
             qDebug()<<"Success authorization";
             m_db.createDB(m_user.getLogin() + ".db");
             m_user.setID(variable(message).toInt());
             qDebug()<<"My ID-> "<<m_user.getID();
             emit signalSendRespond(QString::number( Data::Authorization));
             sendToServer(QString::number( Data::GetListOfFriends));
             break;

         case  Data::Message:
            //  key, idFriend, time, mess
            idSender = variable(message).toInt();
            for(int i = 0; i < 5 ; i++)
            {
                time += variable(message) + ' ';
            }
            qDebug() << message;
            m_idDialog = m_db.searchIdDialog(idSender);
            if(m_idDialog == 0 )
            {
                qDebug() << "The dialog dosn't exist";
                m_db.insertDialog(idSender);
                m_idDialog = m_db.searchIdDialog(idSender);
            }
            m_db.insertMessage(m_idDialog, Data::Get, message, time);
            if(m_idFriend == idSender)
            {
                // str = loginRecipeint, time, messange
                emit signalSendRespond(QString::number( Data::Message) + ' ' + time + ' ' + message);
            }
            break;

         case  Data::File:
         switch(variable(message).toInt())
         {
         case Data::SendFile:
             emit signalSendFileBlock();
             break;

         case Data::Finish:
             emit signalSendRespond(QString::number(Data::File) + ' ' +
                                    "The sending of file is finished");
             m_thread->exit(0);
             break;
         }
             break;

         case  Data::GetListOfFriends:
             qDebug() << "GetNewList";
             emit signalSendRespond(QString::number( Data::GetListOfFriends) + ' ' + message);
             break;
    }
 }

 void Client::ClientConnection::sendToServer(const QString& message)
 {
     if(m_client != nullptr)
     {
         qDebug() << "Client sent-> " << message;
         m_client->write(message.toLocal8Bit());
     }
     else
         qDebug() << "SendToServer: m_client=nullptr";

     if(!m_client->waitForBytesWritten())
     {
         emit signalSendRespond(QString::number(Data::Info) + " Not connection. Try again" );
         return;
     }
 }

 //////////////////////////////////////////////////////

 void Client::ClientConnection::slotRegistration(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);
     sendToServer(QString::number(Data::Registration) + ' ' + login + ' ' + pass);
 }

 void Client::ClientConnection::slotGetListFriend()
 {
    sendToServer(QString::number(Data::GetListOfFriends));
 }


 void Client::ClientConnection::slotChoiceFriend(const int& id)
 {  
     m_idFriend = id;
     qDebug()<<"My id-> " << m_user.getID() << "Friend id-> " << m_idFriend;
     int idDialog = m_db.searchIdDialog(m_idFriend);
     if(idDialog == 0)
     {
         qDebug() << "The dialog doesn't exist";
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
 }

 void Client::ClientConnection::slotAuthorization(const QString& login,const QString& pass)
 {
     m_user.setLogin(login);
     m_user.setPassword(pass);
     sendToServer(QString::number(Data::Authorization) + ' ' + login + ' ' + pass);
 }

 void Client::ClientConnection::slotSendMessage(const QString& message)
 {
     QString mess = message;
     QString time;
     for(int i=0; i<5; i++)
          time += variable(mess) + ' ';
     m_idDialog = m_db.searchIdDialog(m_idFriend);
     if(m_idDialog == 0 )
     {
         qDebug() << "The dialog dosn't exist";
         m_db.insertDialog(m_idFriend);
         m_idDialog = m_db.searchIdDialog(m_idFriend);
     }
     m_db.insertMessage(m_idDialog, Data::Send, mess, time);
     if(m_idFriend != m_user.getID())
     {
         sendToServer(QString::number(Data::Message) + ' ' +
                      QString::number(m_user.getID()) + ' ' +
                      QString::number(m_idFriend) + ' ' +
                      message);
     }
 }

 void Client::ClientConnection::slotSendFile(const QString& path)
 {
     QString fName = path.section("/", -1);
     qDebug() << "File name: "<< fName;
     QFile file(path);
     if(!file.open(QIODevice::ReadOnly))
     {
        qDebug() << "Error";
        return;
     }
     qDebug() << file.size();
     if(m_client)
     {
         sendToServer(QString::number(Data::File) + ' ' +
                      fName + ' ' +
                      QString::number(file.size()).toLatin1());
     }
     else
     {
         qDebug() << "Error with sending file: m_client=nullptr";
     }

     try
     {
         m_thread->setInfo(m_client, path);
         m_thread->start();
     }
     catch( const std::exception& ex)
     {
         qDebug() << ex.what();
     }
 }

 void Client::ClientConnection::slotError(const QString& error)
 {
     qDebug() << "Error... " << error;
     emit signalSendRespond(QString::number(Data::Info) + ' ' + error);

 }


 const QString Client::ClientConnection::variable(QString& str)
 {
    QString res = str.section(' ', 0, 0);
    QString st = str;
    str = st.section(' ',1);
    return res;
 }

