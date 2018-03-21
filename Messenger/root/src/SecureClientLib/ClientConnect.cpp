#include "stdafx.h"

#include "ClientConnect.h"
#include "data.h"

#include "user.h"
#include "idbpresenter.h"
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

     m_clientKey = "-----BEGIN RSA PRIVATE KEY-----"
             "MIIEpQIBAAKCAQEA4LkPwh5YJDpEJjwGoszq1rTKkULBT1BVJng5hHw0W9blAhfg"
             "HtMwyPVN1eLwaXuODCOlKDGmlLy6/0QMn6o5l1emmRQRRBRGpweJ5aNrlE5p3nCx"
             "CmNyK4yCSdzQjJPnCyioCMtXISoJMSDMFRGnVOhpqpNUPtsamdFS5Tbbup/7BeDa"
             "V7ImKyMqoOW113MZJj5APXR78KBjp6MO6Y/CMoMCI4Cug2j1sMcoarOsn4sJVfHs"
             "YSKJJ6qr9DJRzixpXo40gm6hEzrcazfls+ck9uLd67LgUlGwA+bFdgTybe8eGtGO"
             "1ZjBQN73MEkUCif/IKCbrJd/A8W1QfMYjHKkLwIDAQABAoIBAQDUrVBEnwM8BgjJ"
             "RrXhDZ6TZLbxkwPwVE7CAbYttH65DD/gI0hw496f0cjAS+7LZauhwXpk99h3m8Y+"
             "H+Dymt+2Y7W/2kYc8DONkIzpUChYS33Wj0B+XG+I14nW7axR3wgif2/IIulq8aWR"
             "YUDED9kVen/Gd3ibpDEgsgKJ+8kobMltw2ogbMEXw33HQ9RVrQFVy2LA706GNXMy"
             "mjbWwWG+cx779alezNGmTYQck3EW5sge7BfpgKYYuAoCBveJGBM3d/Tg19NkhYkG"
             "lCKaI5PlWvy468v0jOHwndFpP0n4AqKtKOJEF6mISu2OMtK8KK22uvhed61hg27W"
             "RKSBpV1BAoGBAPqgpTOd0MJUaWnd1KhX3VrTxjt5iQVAsZ2HwejBuSBH2OP1zhxS"
             "p+DW5ZZUmYKmfKo8vc2p3Gqr1bcTVxsLapYs+3HAlGzxYAPjKYiEZdap2Pt1WAuc"
             "6bp8zUYHUahaX3Q3gNYzI4/X+L9s/2PkjC0q+HeuzhRK92WdgVhE4t/zAoGBAOWK"
             "Qsiv8jlCDZEJlu6Ni/DUlD99N3GUWFTVoR5LANROGV7/4V7kjYDP2L6WhExWI3mW"
             "7KM7pYwJZOCQFi4kdp8wmkVx7QHb0RUKCFEKoT5qKpktDKdWowEP1ZF/eKqg1SAh"
             "rKZastEw8iWQgJh55K+4iPDfC6NYay9oiFukqzXVAoGBAKE4ocy4Ykf/4OeXKWs5"
             "Sk1ZGZW8sqXMXfVGFTjTFXFshlruDi4uBYwe8QVpWm6vBlbESBx6fi2oaAwixs/A"
             "4knEmeMszM3f37HgeSE2egRCsi/f5kliIQAztCCuKJsxt2GdKqWfs+qeNYd+aDMs"
             "G/gaQkdLDYoER2z4ivHrLj59AoGBAKcB4LNpqKBWWc6UHpe0rwPrd212Kpfd6iLX"
             "SCHlSlYt+LGxFQXY3sfA8h9BHkL4TVlTIRtm830e/KGS1ECAUTpjv2sVh+7ZQ5e+"
             "M+zbAhSKZDIMn+9Eztaf8bCqAV6MJGT7e0WSKhagOR5xs868qVHcvu4aKrqPQ3U7"
             "5jJfbh59AoGAA3FhwpIFJpR8ZCwXkR+3MFghE1Sxuf5RoZT0IFk4/IB+Jkftd8xs"
             "NlHb1ZNBnmCj9ZH3qCn/PeD/jpnP56p6FuugiyosL/4EQMzWm4aZdHdEqvg5FtMl"
             "U/Xiz7aDDpst412OcWSHWEL4zUYqWEEbKY7GBlNGrOe1ysI1KhCaxX8="
             "-----END RSA PRIVATE KEY-----";

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

     m_certClient = "-----BEGIN CERTIFICATE REQUEST-----"
             "MIICojCCAYoCAQAwXTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUx"
             "ITAfBgNVBAoMGEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDEWMBQGA1UEAwwNMTky"
             "LjE2OC4wLjEwMjCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOC5D8Ie"
             "WCQ6RCY8BqLM6ta0ypFCwU9QVSZ4OYR8NFvW5QIX4B7TMMj1TdXi8Gl7jgwjpSgx"
             "ppS8uv9EDJ+qOZdXppkUEUQURqcHieWja5ROad5wsQpjciuMgknc0IyT5wsoqAjL"
             "VyEqCTEgzBURp1ToaaqTVD7bGpnRUuU227qf+wXg2leyJisjKqDltddzGSY+QD10"
             "e/CgY6ejDumPwjKDAiOAroNo9bDHKGqzrJ+LCVXx7GEiiSeqq/QyUc4saV6ONIJu"
             "oRM63Gs35bPnJPbi3euy4FJRsAPmxXYE8m3vHhrRjtWYwUDe9zBJFAon/yCgm6yX"
             "fwPFtUHzGIxypC8CAwEAAaAAMA0GCSqGSIb3DQEBCwUAA4IBAQCy1cc10LUFFc9o"
             "Py3wr2b+nT5GWVVZrYnikqoF7gbijzj7lxqNbnGjEvyZwdpwPV7g7I9ipBVvBHxu"
             "fzdqLdFNA455l43upEAWXjGU0muXsyFT+iypTm2Qy7eN/GUfthDSQsJiKPzrIc6h"
             "y3jZp/geRzWkoimstUxW2tJZDC0sdQPNKRnddDlsE5xqCEdIX1iyBOlv2a6gB+MV"
             "Q7Cfh/pZftID562OGbmnRRdoXCkvCtmqqiIZomm6jNpDiZ7JLBsx5Of2b97jEtRp"
             "+Xw+3l71J0cMXBsgYKPV/TdHWanS6TSjYbPwQ+m+3K4+bKnmHtibO5XtzppCBkFA"
             "gJ0gRAns"
             "-----END CERTIFICATE REQUEST-----";

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

    QSslCertificate certSever(m_certServer.toLocal8Bit());
    QSslCertificate certClient(m_certClient.toLatin1());
    QSslKey key(m_clientKey.toLatin1() ,QSsl::Rsa, QSsl::Pem);


    m_client->setLocalCertificate(certClient);
    m_client->setPrivateKey(key);
    m_client->addCaCertificate(certSever);
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


