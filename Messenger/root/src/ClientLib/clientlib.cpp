#include"stdafx.h"

#include "clientlib.h"


MyClient::MyClient(const QString& strHost,int nPort,QObject* parent) :QObject(parent), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);// создание сокета
    // связь с сервером
    m_pTcpSocket->connectToHost(strHost, nPort);
    // соединение
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    //предоставление данных для чтения
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    //возникновения ошибок
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
}

/*
    вызывется при поступлении данных от сервера
*/

void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);

    /*
    Цикл for нужен, так как не все данные с сервера могут прийти одновременно.
    Поэтому клиент должен быть в состоянии получить как весь блок целиком,
    так и только часть блока или даже все блоки сразу.
    Каждый переданный блок начинается полем, хранящим размер блока.
    */

    while(true) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize; // читаем данные
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime time;
        QString str;
        in >> time >> str;

        qDebug()<<time.toString() + " " + str;

        /*присваиваем атрибуту m_nNextBlockSize значение 0, которое указывает на то,
          что размер очередного блока данных неизвестен.*/

m_nNextBlockSize = 0;
    }
}


  /*  вызывается при возникновении ошибок
*/

void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );

    qDebug()<<strError;
}


void MyClient::sendToServer(const User& us)
{

// для того чтобы записывать все данные блока в него, записывая сначала размер равным 0
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);

    out << quint16(0) << QTime::currentTime() << us.IP<<us.login<<us.password;
   // qDebug()<< quint16(0) << QTime::currentTime() << us;

// перемещаем указатель на начало блока
    out.device()->seek(0);
//записываем размер блока
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInput="";
}



void MyClient::slotConnected()
{
    qDebug()<<"Received the connected() signal";
}



