
#include "SslServer.h"
#include"mythread.h"

#include <QFile>
#include <QSslSocket>

SslServer::SslServer(QObject *parent)
    : QTcpServer(parent)
    ,m_sslLocalCertificate()
    ,m_sslPrivateKey()
    ,m_sslProtocol(QSsl::UnknownProtocol)
    ,m_db(new DBServerPresenter())
    ,m_hash(new QHash<int,QSslSocket*>())
    ,m_countThread(0)
    ,m_maxCountThreads(20)
{
}


SslServer::~SslServer()
{
}

void SslServer::start(int port)
{
    //set sertificate and private key
    setSslLocalCertificate("../../secure/sslserver.pem");
    setSslPrivateKey("../../secure/sslserver.key",QSsl::Rsa, QSsl::Pem,"password");

    //set version TLS 2.1
    setSslProtocol(QSsl::TlsV1_2);

    //start listening
    if (listen(QHostAddress::Any, port))
    {
        qDebug() << "Now listening on:" << port;
    }
    else
        qDebug() << "ERROR: could not bind to:" << port;


}


void SslServer::incomingConnection(qintptr socketDescriptor)
{
    m_socketDescriptor=socketDescriptor;
    while(true)
    {
        if(m_countThread<m_maxCountThreads)
        {
            ++m_countThread;
            // Every new connection will be run in a newly created thread
            QPointer<MyThread> thread= new MyThread(socketDescriptor,m_db,m_hash, this);

            connect(thread,&MyThread::error,this,&SslServer::slotSslError);

            // once a thread is not needed, it will be beleted later
            connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

            connect(thread, &QThread::destroyed, this, &SslServer::slotFinished);
            connect(thread, &QThread::finished, this, &SslServer::slotFinished);


            thread->start();

           return;
        }
    }
}

void SslServer::slotSslError(const QAbstractSocket::SocketError& errors)
{
      qDebug()<<errors;
}

void SslServer::slotFinished()
{
    --m_countThread;
}




///////////////////////////////////////////////////////////////////////////
const QSslCertificate &SslServer::getSslLocalCertificate() const
{
    return m_sslLocalCertificate;
}

const QSslKey &SslServer::getSslPrivateKey() const
{
    return m_sslPrivateKey;
}

QSsl::SslProtocol SslServer::getSslProtocol() const
{
    return m_sslProtocol;
}



void SslServer::setSslLocalCertificate(const QSslCertificate &certificate)
{
    m_sslLocalCertificate = certificate;
}

bool SslServer::setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format)
{
    QFile certificateFile(path);

    if (!certificateFile.open(QIODevice::ReadOnly))
        return false;

    m_sslLocalCertificate = QSslCertificate(certificateFile.readAll(), format);
    return true;
}


void SslServer::setSslPrivateKey(const QSslKey &key)
{
    m_sslPrivateKey = key;
}

// set private key
bool SslServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat format, const QByteArray &passPhrase)
{
    QFile keyFile(fileName);

    if (!keyFile.open(QIODevice::ReadOnly))
        return false;

    m_sslPrivateKey = QSslKey(keyFile.readAll(), algorithm, format, QSsl::PrivateKey, passPhrase);
    return true;
}


void SslServer::setSslProtocol(QSsl::SslProtocol protocol)
{
    m_sslProtocol = protocol;
}
