#include "stdafx.h"

#include "SslServer.h"
#include "mythread.h"

 Server::SslServer::SslServer(QObject *parent)
    : QTcpServer(parent)
    , m_db(new DB::DBServerPresenter())
    , m_hash(new QHash<int,QSslSocket*>())
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
}

void  Server::SslServer::start(const int& port)
{
    //start listening
    if (listen(QHostAddress::Any, port))
    {
        qDebug() << "Now listening on:" << port;
    }
    else
        qDebug() << "ERROR: could not bind to:" << port;

}


void  Server::SslServer::incomingConnection(qintptr socketDescriptor)
{
            // Every new connection will be run in a newly created thread
            thread = new MyThread(socketDescriptor, m_db, m_hash, this);

            connect(thread,&MyThread::error,this,&SslServer::slotSslError);

            // once a thread is not needed, it will be beleted later
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
            connect(thread, &QThread::destroyed, this, &QThread::destroyed);


            thread->start();
}

void  Server::SslServer::slotSslError(const QAbstractSocket::SocketError& errors)
{
      qDebug()<<errors;
}

