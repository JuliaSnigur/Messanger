#include "stdafx.h"


#include"user.h"
#include"request.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include "dbserverpresenter.h"

#include"parsedata.h"

#include"ServerSocket.h"

using namespace ServerNamespace;
using namespace StringHandlNamespace;

ServerSocket::ServerSocket(QWidget*pwgt):QWidget(pwgt),m_db(),m_hash(),m_flag(true),m_QueueRequest()
{
    qDebug()<<"Server:";
}



ServerSocket::~ServerSocket(){}

ServerSocket::ServerSocket(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt), m_nNextBlockSize(0), m_db()
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
        qDebug()<<"Creat socket";
        connect(m_ptcpServer, SIGNAL(newConnection()),this, SLOT(slotNewConnection()));
    }


}

void ServerSocket::createServer(int nPort)
{
    m_ptcpServer = new QTcpServer(this);

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



// ----------------------------------------------------------------------
 void ServerSocket::slotNewConnection()
{

    //возврат сокета nextPendingConnection, посредством которого можно осуществлять дальнейшую связь с клиентом
    m_ClientSocket =  m_ptcpServer->nextPendingConnection();


    //дисконектим пользователя
    connect(m_ClientSocket, SIGNAL(disconnected()),m_ClientSocket, SLOT(deleteLater()));
    connect(m_ClientSocket,&QTcpSocket::disconnected, this, &ServerSocket::slotDisconnect);
    //При поступлении запросов от клиентов
    //отправляется сигнал readyToRead ( ) , который мы соединяем со слотом slotReadClient().
    connect(m_ClientSocket, SIGNAL(readyRead()),this, SLOT(slotReadClient()));

    sendToClient(m_ClientSocket, QString::number(Connection)+" Server Response: Connected!");

     qDebug()<<"New connection";   

}


// ----------------------------------------------------------------------
void ServerSocket::slotReadClient()
{
    //преобразование указателя sender к типу QTcpSocket.
    m_ClientSocket = (QTcpSocket*)sender();
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


        m_QueueRequest.push_back(req);

        if(!m_flag)// сервер занят
            break;

        m_flag=false;

        req=m_QueueRequest.front();
        m_QueueRequest.pop_front();

         qDebug()<<"QUEUE is poped: "<<req;

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

        m_flag=true;


    }

    //обнуляем размер блока что бы проводить запись следующего блока
     m_nNextBlockSize = 0;
}

// ----------------------------------------------------------------------
void ServerSocket::sendToClient(QTcpSocket* pSocket, const QString& str)
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

    //записываем созданный блок
    pSocket->write(arrBlock);
   // pSocket->waitForBytesWritten(1000);

}

void ServerSocket::registration(QString& req)
{

    int id=0;

    QString log=variable(req), pas=variable(req);
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
    m_flag=true;
}

void ServerSocket::slotDisconnect()
{
    // ошибка
    QHash<int,QTcpSocket*>::iterator iter=m_hash.begin();
    while(iter!=m_hash.end())
    {
        if(!iter.value()->state()==QAbstractSocket::ClosingState)
        {
            m_hash.erase(iter);
            qDebug()<<"Dissconect";
        }
         ++iter;
    }
}



  void ServerSocket::sendToAllClients( const QString& str)
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


void ServerSocket::message(QString& str)
{
    // id friend
    int myID=variable(str).toInt();
    int friendID=variable(str).toInt();

    QString login=m_db.searchLogin(myID);

    if(login!="")
         sendToClient(m_hash[friendID],QString::number(Message)+' '+login+": "+str);
    else
        sendToClient(m_hash[myID],QString::number(Error)+" The message dosn't send");


}

void ServerSocket::sendList()
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
      qDebug()<<"Vector: "+concatenationVec(vec);
     sendToAllClients(QString::number(GetNewList)+' '+concatenationVec(vec));
  }
  else
    {
        qDebug()<<m_hash.size()<< " client";
        sendToAllClients(QString::number(Error)+" Just 1 connection");
    }
}

