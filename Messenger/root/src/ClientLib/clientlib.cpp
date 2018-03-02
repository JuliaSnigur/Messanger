#include"stdafx.h"
#include "clientlib.h"



MyClient::~MyClient()
{
    if(this->m_pTcpSocket)
        delete m_pTcpSocket;
}

MyClient::MyClient(QObject* parent):QObject(parent), m_nNextBlockSize(0),file(0)
{}


void MyClient::createConnection(const QString& strHost, int nPort)
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
    QString answer;
    QTime time;

    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_4_2);


    //Цикл for нужен, так как не все данные с сервера могут прийти одновременно.
    //Поэтому клиент должен быть в состоянии получить как весь блок целиком,
    //так и только часть блока или даже все блоки сразу.
    //Каждый переданный блок начинается полем, хранящим размер блока.


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


        in >>time>>answer;

        qDebug()<<"Client got-> "<<time.toString() + " " + answer;

        switch((ParseData::variable(answer)).toInt())
        {

        case Connection:

                qDebug()<<answer;

                break;

        case Registration:

            //если true - только true, список кто онлайн
            // false - false и сообщение об ошибке
            if((ParseData::variable(answer)).toInt())
                {
                    qDebug()<<"Good)";

                }
                else
                {
                    qDebug()<<"Wrong(";
                }

                break;

            case Authorization:

                //если true - только true, список кто онлайн
                // false - false и сообщение об ошибке

                break;

            case Message:


                break;

            case File:


                break;

        };



}
      //  qDebug()<<time.toString() + " " + str;

        //присваиваем атрибуту m_nNextBlockSize значение 0, которое указывает на то,
         // что размер очередного блока данных неизвестен.

        m_nNextBlockSize = 0;
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


void MyClient::sendToServer( const QString& data)
{

// для того чтобы записывать все данные блока в него, записывая сначала размер равным 0
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);

    out << quint16(0) << QTime::currentTime() <<data;
    qDebug()<< QTime::currentTime() << data;


    // перемещаем указатель на начало блока
    out.device()->seek(0);

    //записываем размер блока
    out << quint16(arrBlock.size() - sizeof(quint16));

    // отправка блока на сервер
    m_pTcpSocket->write(arrBlock);


}



void MyClient::slotConnected()
{
    qDebug()<<"Received the connected() signal";
}


/*

void MyClient::sendFile(const QString& fileName)
{


    if(file != NULL)
    {
        return;
     }

    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);

      file = new QFile(fileName);
      if(file->open(QFile::ReadOnly))
      {

          // подготовка данных для записи //
          m_pTcpSocket->write(data);
          m_pTcpSocket->waitForBytesWritten();
          connect(m_pTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(sendPartOfFile()));
          sendPartOfFile();
      }
      else
      {
        emit this->slotError(QString("File not can open for read"));
        return;
      }
}


void MyClient::sendPartOfFile() {

  char block[SIZE_BLOCK_FOR_SEND_FILE];

  if(!file->atEnd())
  {
    qint64 in = file->read(block, sizeof(block));
    qint64 send = m_pTcpSocket->write(block, in);
  }
  else
  {
    file->close();
    file = NULL;
    disconnect(m_pTcpSocket, SIGNAL(bytesWritten(qint64)), this, SLOT(sendPartOfFile()));
    emit endSendFile();
  }
}

void MyClient::receiveFile(QString fileName) {
  QString savePath = "Downloads/";
  QDir dir;
  dir.mkpath(savePath);
  file = new QFile(savePath + fileName);
  m_nNextBlockSize = 0;
  receiveFile();
}



void MyClient::receiveFile()
{
  QDataStream in(clientSocket);
   if(!bufferForUnreadData.isEmpty())
   {
        receiveFile->write(bufferForUnreadData);
        sizeReceivedData += bufferForUnreadData.size();
        bufferForUnreadData.clear();
   }

  char block[SIZE_BLOCK_FOR_SEND_FILE];

  while(!in.atEnd())
  {
    qint64 toFile = in.readRawData(block, sizeof(block));
    sizeReceivedData += toFile;
    receiveFile->write(block, toFile);
  }
  if(sizeReceivedData == sizeReceiveFile)
  {
    receiveFile->close();
    receiveFile = NULL;
    sizeReceiveFile = 0;
    sizeReceivedData = 0;
  }
}

*/
