#include "filethread.h"

#include "data.h"


Client::FileThread::FileThread(QObject *parent)
            : QThread(parent)
            , m_file(new QFile())
{
}

Client::FileThread::~FileThread(){}

void Client::FileThread::setInfo(std::shared_ptr<QSslSocket> client, const QString& fileName)
{
    m_file->close();
    m_client = client;
    m_file->setFileName(fileName);
    if(!m_file->open(QIODevice::ReadOnly))
    {
        emit signalError(QString::number(Data::Info) + ' ' + "Error with reading file");
        throw std::exception( "Error with reading file");
    }
    qDebug() << "File's opening";
}



 void Client::FileThread::run()
 {
     exec();
 }

  void Client::FileThread::sendFileBlock()
  {
      static qlonglong size = 0;
      QByteArray block;
      if(!m_file->atEnd())
      {
          block = m_file->read(4096);
          size += block.size();
          qDebug()<<"Read: " << size << ' ' << block.size();
          if(m_client)
          {
              m_client->write(block, block.size());
          }
          else
          {
              emit signalError(QString::number(Data::Info) + ' ' + "Error with sending file");
          }
      }
      else
      {
         m_file->close();
         qDebug() << "Finished";

      }
  }
