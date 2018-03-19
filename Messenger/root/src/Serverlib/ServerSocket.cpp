#include "stdafx.h"


#include"user.h"
#include"request.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include "dbserverpresenter.h"

#include"parsedata.h"

#include"ServerSocket.h"




ServerNamespace::ServerSocket::ServerSocket(QObject*pwgt):QObject(pwgt),m_db(),m_hash()
{
    qDebug()<<"Server:";
}



ServerNamespace::ServerSocket::~ServerSocket(){}

ServerNamespace::ServerSocket::ServerSocket(int nPort, QObject* pwgt /*=0*/) : QObject(pwgt), m_nNextBlockSize(0), m_db()
{
    qDebug()<<"Server:";
    m_ptcpServer = new QTcpServer(this);

   // catch the port
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0, "Server Error","Unable to start the server:"+ m_ptcpServer->errorString());
        m_ptcpServer->close();

    }
    else
    {
        qDebug()<<"Create socket";
        connect(m_ptcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }


}

void ServerNamespace::ServerSocket::createServer(int nPort)
{
    m_ptcpServer = new QTcpServer(this);

    if(m_ptcpServer!=nullptr)
    {
        // catch the port
        if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
            QMessageBox::critical(0, "Server Error","Unable to start the server:"+ m_ptcpServer->errorString());
            m_ptcpServer->close();

        }
        else
        {
            qDebug()<<"Creat socket";
            connect(m_ptcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
        }
    }
    else
        qDebug()<<"Create Server:: ptr=nullptr";
}



// ----------------------------------------------------------------------
 void ServerNamespace::ServerSocket::slotNewConnection()
{

    //возврат сокета nextPendingConnection, посредством которого можно осуществлять дальнейшую связь с клиентом
    m_ClientSocket =  m_ptcpServer->nextPendingConnection();

    if(m_ClientSocket!=nullptr)
    {
        //дисконектим пользователя
        connect(m_ClientSocket, SIGNAL(disconnected()),m_ClientSocket, SLOT(deleteLater()));
        connect(m_ClientSocket,&QTcpSocket::disconnected, this, &ServerSocket::slotDisconnect);
        //При поступлении запросов от клиентов
        //отправляется сигнал readyToRead ( ) , который мы соединяем со слотом slotReadClient().
        connect(m_ClientSocket, SIGNAL(readyRead()),this, SLOT(slotReadClient()));

        sendToClient(m_ClientSocket, QString::number(Connection)+" Server Response: Connected!");

         qDebug()<<"New connection";
    }
    else
        qDebug()<<"NewConnection: ptr_Client=nullptr";
}


// ----------------------------------------------------------------------
void ServerNamespace::ServerSocket::slotReadClient()
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
void ServerNamespace::ServerSocket::sendToClient(QTcpSocket* pSocket, const QString& message)
{
    if (pSocket != nullptr)
    {

        qDebug()<<"Server sent-> "<< QTime::currentTime() << message;
        pSocket->write(message.toLocal8Bit());
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

