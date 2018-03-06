#include"stdafx.h"

#include"parsedata.h"
#include "secureclientlib.h"


SecureClient::SecureClient(QObject* obj):QObject(obj),m_Client(nullptr)
{
    /*
    connect(socket, SIGNAL(encrypted()), this, SLOT(ready()));
     connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
     connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
     connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
*/
}

SecureClient::~SecureClient(){}


void SecureClient::createConnection(const QString& strHost, int nPort)
{

        m_Client=new QSslSocket(this);

        QSslConfiguration sslConfiguration;

        QByteArray key;
        QByteArray cert;

        QFile certFile("../../src/SecureClientLib/client.crt");
        QFile keyFile("../../src/SecureClientLib/client.key");

         m_Client = new QSslSocket(this);


         if(!keyFile.exists() ||!certFile.exists() )
          {
             qDebug()<<"File dosn't exist";
             return;
         }


         if(keyFile.open(QIODevice::ReadOnly))
         {
             key = keyFile.readAll();
             keyFile.close();
         }
         else
         {
             qDebug() << keyFile.errorString();
             return;
         }

         if(certFile.open(QIODevice::ReadOnly))
         {
             cert = certFile.readAll();
             certFile.close();
         }
         else
         {
             qDebug() << certFile.errorString();
             return;
         }

         QSslCertificate certificate(cert, QSsl::Pem);

         QSslKey sslKey(key, QSsl::Rsa, QSsl::Pem);


         sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
         sslConfiguration.setLocalCertificate(certificate);
         sslConfiguration.setPrivateKey(sslKey);
         sslConfiguration.setProtocol(QSsl::TlsV1SslV3);

            m_Client->setSslConfiguration(sslConfiguration);


        m_Client->connectToHostEncrypted(strHost, nPort);
        qDebug()<<"There is connection";
       // m_Client->startClientEncryption();

}

//  вызывается при возникновении ошибок
void SecureClient::slotError(QAbstractSocket::SocketError err)
{
  QString strError =
      "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                   "The host was not found." :
                   err == QAbstractSocket::RemoteHostClosedError ?
                   "The remote host is closed." :
                   err == QAbstractSocket::ConnectionRefusedError ?
                   "The connection was refused." :
                   QString(m_Client->errorString())
                  );

  qDebug()<<strError;
}
/*

void SecureClient::slotConnected()
{
      qDebug()<<"Received the connected() signal";
}


void SecureClient::slotSslErrors(const QList<QSslError> &errors)
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

}


  void SecureClient::slotReadyRead()
  {
      QString answer;
      QTime time;

      QDataStream in(m_SslSocket);
      in.setVersion(QDataStream::Qt_4_2);


      //Цикл for нужен, так как не все данные с сервера могут прийти одновременно.
      //Поэтому клиент должен быть в состоянии получить как весь блок целиком,
      //так и только часть блока или даже все блоки сразу.
      //Каждый переданный блок начинается полем, хранящим размер блока.

      while(true) {
          if (!m_nNextBlockSize) {

              if (m_SslSocket->bytesAvailable() < sizeof(quint16)) {
                  break;
              }

              in >> m_nNextBlockSize; // читаем данные
          }

          if (m_SslSocket->bytesAvailable() < m_nNextBlockSize) {
              break;
          }


          in >>time>>answer;
          qDebug()<<"Client got-> "<<time << ' ' << answer;



          switch((StringHandlNamespace::variable(answer)).toInt())
          {

          case Error:
              qDebug()<<"Upss.. "<<answer;
              break;

          case Connection:

                  qDebug()<<answer;

                  break;

          case Registration:

              qDebug()<<"Success registration";

              // insert user into tables session
                emit signalInsertUserIntoTabSession();

              qDebug()<<"GetID";
              emit signalGetID(StringHandlNamespace::variable(answer).toInt());

              // get lists of clients who are online
              slotSendToServer(QString::number(GetNewList));




                  break;

              case Authorization:
                  break;

              case Message:
              qDebug()<<answer;

              emit signalSendMessage();
                  break;

              case File:
                  break;

          case GetNewList:
              qDebug()<<"GetNewList";
              emit signalGetListsClients(StringHandlNamespace::separateVec(answer));
              break;

          };

  }
          //присваиваем атрибуту m_nNextBlockSize значение 0, которое указывает на то,
           // что размер очередного блока данных неизвестен.

          m_nNextBlockSize = 0;


      }


*/
