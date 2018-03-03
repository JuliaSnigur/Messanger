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

ServerSocket::ServerSocket(QWidget*pwgt):QWidget(pwgt),m_db(),m_us()
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
   QTcpSocket*  pClientSocket =  m_ptcpServer->nextPendingConnection();


    //дисконектим пользователя
    connect(pClientSocket, SIGNAL(disconnected()),pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket,&QTcpSocket::disconnected, this, &ServerSocket::slotDisconnect);
    //При поступлении запросов от клиентов
    //отправляется сигнал readyToRead ( ) , который мы соединяем со слотом slotReadClient().
    connect(pClientSocket, SIGNAL(readyRead()),this, SLOT(slotReadClient()));

    sendToClient(pClientSocket, QString::number(Connection)+" Server Response: Connected!");

     qDebug()<<"New connection";   

}


// ----------------------------------------------------------------------
void ServerSocket::slotReadClient()
{
    //преобразование указателя sender к типу QTcpSocket.
   QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    //цикл обработки частей блоков информации передаваемой и принимаемой по сети
    while (true)
    {
        if (!m_nNextBlockSize)
        { //в if проверяем размер блока не менее 2 байт и m_nNextBlockSize (размер блока) неизвестен

            if (pClientSocket->bytesAvailable() < (int)sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize; //считываем вносим данные
        }
        //если размер полученных данных менее размера блока данных то данные не записываем
        if (pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        //если размер данных для чтения равен или более размера блока
        //тогда данные считываются из потока в time и str
        QTime   time;
        QString req;

        in >> time >> req;

        User us;

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

        registration(pClientSocket,req);

        break;

        case Authorization:
        qDebug()<<"Authorization\n";



        break;

        default:
            break;
        }




        //обнуляем размер блока что бы проводить запись следующего блока
        m_nNextBlockSize = 0;

    }
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
    pSocket->waitForBytesWritten();

}

void ServerSocket::registration(QTcpSocket* pSocket,QString& req)
{
    m_us.setLogin(variable(req));
    m_us.setPassword(variable(req));

    // insert user into db
    qDebug()<<"User: "<<m_us.getLogin()<<", "<<m_us.getPassword();
    m_db.insertUser(m_us);

    int id=m_db.searchID(m_us.getLogin());

    if(id<0)
    {
        qDebug()<<"The id doesn't exist";
    }
    else
    {
         qDebug()<<"ID: "<<id;
         m_us.setID(id);
         m_vecClientsID.push_back(id);

         QTcpSocket* p=new QTcpSocket(this);
         p=pSocket;
         m_vecSockets.push_back(p);

        sendToClient(pSocket,QString::number(Registration));

        sendToClient(pSocket,QString::number(GetID)+" "+QString::number(m_us.getID()));

        if(m_vecClientsID.size()>1)
            sendToAllClients(QString::number(GetNewList)+' '+concatenationVec(m_vecClientsID));
        else
          qDebug()<<m_vecClientsID.size()<< " client";

 }

}

void ServerSocket::slotDisconnect()
{
    bool flag;
    int i=0;

    do
    {
        flag=false;
        if(m_us.getID()==m_vecClientsID[i])
            flag=true;
        else
           if(i<m_vecClientsID.size())
               ++i;


    }while(i<m_vecClientsID.size()||!flag);

    m_vecClientsID.erase(m_vecClientsID.begin()+i);
    m_vecSockets.erase(m_vecSockets.begin()+i);
}



  void ServerSocket::sendToAllClients( const QString& str)
  {
      for(int i=0;i<m_vecSockets.size();i++)
          sendToClient(m_vecSockets[i],str);  
  }

/*
bool ServerSocket::authorization(QString&);
*/


void ServerSocket::message(QString& str)
{
    int id=variable(str).toInt();
    int index=0;

    qDebug()<<"ID->"<<id;

   for( index=0;index<m_vecClientsID.size();index++)
       if(id==m_vecClientsID[index])
           break;

    if(index<m_vecClientsID.size()|| str!="")
    {
        qDebug()<<"Index: "<<index;

        sendToClient(m_vecSockets[index],QString::number(Message)+' '+m_us.getLogin()+": "+str);
     }
    else
        sendToClient(m_vecSockets[index],QString::number(Error));

}



