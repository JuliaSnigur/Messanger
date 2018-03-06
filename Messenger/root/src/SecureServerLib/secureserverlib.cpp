#include"stdafx.h"

#include "secureserverlib.h"


SecureServer::SecureServer():m_Server(nullptr),m_nNextBlockSize(0)
{

}

SecureServer::~SecureServer(){}


void SecureServer::createServer(int port)
{
    m_Server = new QSslSocket(this);

    if (listen(QHostAddress::Any, port))
    {
        qDebug() << "SSL Server listening on port" << port;
        connect(m_Server, &QSslSocket::connected,this, &SecureServer::slotNewConnection);

    }
    else
        qDebug()<<"Error";
}

 void SecureServer::slotNewConnection()
{
      m_Client = (QSslSocket*)nextPendingConnection();
     incomingConnection(m_Client->socketDescriptor());


    // connect(m_Server, &QSslSocket::sslErrors, this, &SecureServer::slotSslError);
     connect(m_Server, &QSslSocket::encrypted, this, &SecureServer::slotEcrypted);
     connect(m_Server, &QSslSocket::readyRead, this, &SecureServer::slotReadClient);


     if(m_Client!=nullptr)
        connect(m_Client,&QSslSocket::readyRead, this, &SecureServer::slotDisconnect);
     else
        qDebug()<<"m_client=nullptr";
}

 void SecureServer::incomingConnection(int handle)
 {
     QSslConfiguration sslConfiguration;

     QByteArray key;
     QByteArray cert;

     QFile certFile("../../src/SecureServerLib/server.crt");
     QFile keyFile("../../src/SecureServerLib/server.key");

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
      sslConfiguration.setProtocol(QSsl::SslV3);

         m_Server->setSslConfiguration(sslConfiguration);


         if (!m_Server->setSocketDescriptor(handle))
             {
                 qDebug() <<"! Couldn't set socket descriptor";
                 delete m_Server;

                 return;
             }
         else
          {
             qDebug()<<"New connection";
             m_Server->startServerEncryption();
}

 }

 void SecureServer::slotSslError(const QList<QSslError> &errors)
 {
     qDebug() << m_Server->errorString();
 }

 void SecureServer::slotEcrypted()
 {
     qDebug()<<"Ecrypted";
 }

 void  SecureServer::slotDisconnect()
 {
     qDebug()<<"Disconnect";
 }

 void  SecureServer::slotReadClient()
 {
     QByteArray qstrbytes = m_Server->readLine();
         qDebug() << qstrbytes;
     qDebug()<<"slotReadClient";
 }


/*
// ----------------------------------------------------------------------
void SecureServer::slotReadClient()
{
    //преобразование указателя sender к типу QTcpSocket.
    if(sender()!=nullptr)
    {
        m_ClientSocket = (QTcpSocket*)sender();
    }
    else
    {
        qDebug()<<"Sender=nullptr";
    }

    QDataStream in(m_ClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    //цикл обработки частей блоков информации передаваемой и принимаемой по сети
    while (true)
    {
        if (!m_nNextBlockSize)
        { //в if проверяем размер блока не менее 2 байт и m_nNextBlockSize (размер блока) неизвестен

            if (m_ClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize; //считываем вносим данные
        }
        //если размер полученных данных менее размера блока данных то данные не записываем
        if (m_ClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        //если размер данных для чтения равен или более размера блока
        //тогда данные считываются из потока в time и str
        QTime   time;
        QString req;

        in >> time >> req;

        // преобразуем time в строку и вместе с str записываем в strMessage
        //добавляем в виджет strMessage
        qDebug()<< time.toString() << " " << "Client has sent - " << req;


        switch ((StringHandlNamespace::variable(req)).toInt())
        {

        case Error:
            qDebug()<<"Upss..";
            break;
        case Message:

        qDebug()<<"MESSAGE\n";

        message(req);
        break;

        case Registration:
        qDebug()<<"Registration\n";

        registration(req);

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

    //обнуляем размер блока что бы проводить запись следующего блока
     m_nNextBlockSize = 0;
}

// ----------------------------------------------------------------------
void ServerNamespace::ServerSocket::sendToClient(QTcpSocket* pSocket, const QString& str)
{ //формируем данные клиенту
    // поскольку размер файла должен быть выслан первым перед блоком информации то создаем arrBlock с значением ноль
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_3);
    //определяем значение первого бита в памяти текущего блока данных и начинаем записывать данные
    out << quint16(0) << QTime::currentTime() << str;
    qDebug()<<"Server sent-> " << QTime::currentTime() << str;
    //ищем созданное нами нулевое значение что бы определить начало блока (перенос указателя в начало блока)
    out.device()->seek(0);
    //вычисляем размер блока данных
    out << quint16(arrBlock.size() - sizeof(quint16));

    if (pSocket != nullptr)
    {

          pSocket->write(arrBlock);
    }
    else
    {
        qDebug() << "Invalid socket ptr";
    }
}

void ServerNamespace::ServerSocket::registration(QString& req)
{

    int id=0;

    QString log=StringHandlNamespace::variable(req), pas=StringHandlNamespace::variable(req);
    User us(log,pas);

    // insert user into db
    qDebug()<<"User: "<<us.getLogin()<<", "<<us.getPassword();

    if(!m_db.insertUser(us))
      {
        sendToClient(m_ClientSocket,QString::number(Error)+" The login is exist");
        return;
      }
     id=m_db.searchID(us.getLogin());

    if(id<0)
    {
        qDebug()<<"The id doesn't exist";
    }
    else
    {
         qDebug()<<"ID: "<<id;
         us.setID(id);


         m_hash.insert(id,m_ClientSocket);

        sendToClient(m_ClientSocket,QString::number(Registration)+" "+QString::number(us.getID()));
 }
}

void ServerNamespace::ServerSocket::slotDisconnect()
{
    QHash<int,QTcpSocket*>::iterator iter=m_hash.begin();
    while(iter!=m_hash.end())
    {
        if(iter.value()->state()==QAbstractSocket::UnconnectedState)
        {
            m_hash.erase(iter);
            qDebug()<<"Dissconect";
            return;
        }
         ++iter;
    }

     sendList();

}



  void ServerNamespace::ServerSocket::sendToAllClients( const QString& str)
  {
      QHash<int,QTcpSocket*>::iterator iter=m_hash.begin();
      while(iter!=m_hash.end())
      {
           sendToClient(iter.value(),str);
            ++iter;
      }
  }

/*
bool ServerSocket::authorization(QString&);
*/

/*
void ServerNamespace::ServerSocket::message(QString& str)
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

void ServerNamespace::ServerSocket::sendList()
{
    QVector<int> vec;
    QHash<int,QTcpSocket*>::iterator iter;

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
*/





