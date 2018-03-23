#include "filethread.h"

#include <QDataStream>

Client::FileThread::FileThread(std::shared_ptr<QSslSocket> client,const QString& fileName,  QObject *parent)
            : QThread(parent)
            , m_fileName(fileName)
            , m_file()
            , m_client(client)
{
}

Client::FileThread::~FileThread(){}


 void Client::FileThread::run()
 {

       m_file.setFileName(m_fileName);
        if(!m_file.open(QIODevice::ReadOnly))
        {
            qDebug()<<"Error reading file for sending";
            return;
        }

     QByteArray data;

     while(1)
         {
             data.clear();
             data = m_file.read(32768*8);
             qDebug() << "Read : " << m_file.size();
             if(data.size()==0)
                 break;
             qDebug() << "Written : " << m_client->write(data);
             m_client->waitForBytesWritten();
             data.clear();
         }
 }
