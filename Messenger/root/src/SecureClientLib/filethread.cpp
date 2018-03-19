#include "filethread.h"

FileThread::FileThread(std::shared_ptr<QSslSocket> client,const QString& fileName,  QObject *parent)
            : QObject(parent)
            , m_fileName(fileName)
            , m_file()
            , m_client(client)
{
}

FileThread::~FileThread(){}


 void FileThread::run()
 {
     m_file.setFileName(m_fileName);
     char block[1024];
     qint64 in;

    if(!m_file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Error reading file for sending";
        return;ss
    }

     while(!m_file.atEnd())
     {
       in = m_file.read(block, sizeof(block));
       qDebug()<<"Read: " << in;
       m_client->write(block, in);
     }
       m_file.close();
 }
