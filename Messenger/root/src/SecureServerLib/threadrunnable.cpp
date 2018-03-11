#include"stdafx.h"
#include "threadrunnable.h"



#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"


#include"parsedata.h"

// QHash<int,QSslSocket*> ThreadRunnable::m_hash;
// DBServerPresenter ThreadRunnable::m_db ;


ThreadRunnable::ThreadRunnable(QSslSocket* socket,QObject* obj)
    :QObject(obj)
    ,m_mutexDB()
    ,m_mutexHashTab()
    ,m_sslClient(socket)
{
}




ThreadRunnable::~ThreadRunnable(){}


/*void
ThreadRunnable::getSocket(QSslSocket* socket)
{
    m_sslClient=socket;
}
*/


void ThreadRunnable::run()
{
    connect(m_sslClient, SIGNAL(readyRead()),this, SLOT(slotReadyRead()),Qt::DirectConnection);
    connect(m_sslClient,SIGNAL(disconnected()),this, SLOT(slotDisconnect()));
    connect( m_sslClient, SIGNAL(sslErrors(QList<QSslError>)), SLOT(slotSslError(QList<QSslError>)),Qt::DirectConnection);

    qDebug()<<"The thread started";

    sendToClient(m_sslClient,QString::number(Connection)+" Hello Client");
}

void ThreadRunnable::slotSslError(QList<QSslError> errors)
{
    QString erroStr="";
    foreach (const QSslError &e, errors)
        erroStr.append(e.errorString()).append("\n");

   qDebug()<<erroStr;

    m_sslClient->ignoreSslErrors();
}

void ThreadRunnable::sendToClient(QSslSocket* pSocket,const QString& message)
{
    if (pSocket != nullptr)
    {
        qDebug()<<"Server sent-> "<< QTime::currentTime().toString()+' '+message;
        pSocket->write( (QTime::currentTime().toString()+' '+message).toLocal8Bit());
    }    else
    {
        qDebug() << "Invalid socket ptr";
    }
}


 void ThreadRunnable::slotReadyRead()
 {
     m_sslClient = (QSslSocket*)sender();

     QString mess = m_sslClient->readAll();    // Read message
     qDebug() << "Client has sent -" << mess;


 }


 void ThreadRunnable::registration(QString& req)
 {

 }

 void ThreadRunnable::authorization(QString& str)
 {
 }


 void ThreadRunnable::sendList()
 {

}


 void ThreadRunnable::message(QString& str)
 {

 }


 void ThreadRunnable::slotDisconnect()
 {

}



