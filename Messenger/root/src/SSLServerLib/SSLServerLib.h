#pragma once
#include "stdafx.h"

class SslServer : public QTcpServer{
    Q_OBJECT
public:
    SslServer(QObject * parent = 0);
    ~SslServer();
    void setSslLocalCertificate(const QSslCertificate &certificate);
    bool setSslLocalCertificate(const QString &path, QSsl::EncodingFormat format = QSsl::Pem);
    void setSslPrivateKey(const QSslKey &key);
    bool setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa,
                          QSsl::EncodingFormat format = QSsl::Pem, const QByteArray &passPhrase = QByteArray());
    void setSslProtocol(QSsl::SslProtocol protocol);
    void incomingConnection(qintptr socketDescriptor) override;
    QSslSocket *getConnectedSocket();
private:
    QSslCertificate m_sslLocalCertificate;
    QSslKey m_sslPrivateKey;
    QSsl::SslProtocol m_sslProtocol;
};
