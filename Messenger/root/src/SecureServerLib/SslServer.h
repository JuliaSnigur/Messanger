#pragma once

#include <QTcpServer>
#include <QString>
#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>
#include<QSslSocket>
#include<QPointer>


#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"



class SslServer : public QTcpServer
{
    Q_OBJECT

public:
    SslServer(QObject *parent = 0);
    virtual ~SslServer();

    void start(int port);

    const QSslCertificate &getSslLocalCertificate() const;
    const QSslKey &getSslPrivateKey() const;
    QSsl::SslProtocol getSslProtocol() const;


    void setSslLocalCertificate(const QSslCertificate &certificate);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);

    void setSslPrivateKey(const QSslKey &key);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa, QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());

    void setSslProtocol(QSsl::SslProtocol protocol);


signals:
    void signalStartThread();

public slots:
     void slotSslError(const QAbstractSocket::SocketError& errors);
     void slotFinished();

protected:
    void incomingConnection(qintptr socketDescriptor) override final;


private:
    QSslCertificate m_sslLocalCertificate;
    QSslKey m_sslPrivateKey;
    QSsl::SslProtocol m_sslProtocol;
    QSslSocket *sslSocket ;

    QHash<int,QSslSocket*>* m_hash;
    DBServerPresenter* m_db;

    int m_countThread;
    int m_maxCountThreads;

    qintptr m_socketDescriptor;
};

