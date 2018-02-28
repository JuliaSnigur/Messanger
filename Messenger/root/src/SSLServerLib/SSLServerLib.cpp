#include "stdafx.h"
#include "SSLServerLib.h"
#include <openssl/aes.h>

SslServer::SslServer(QObject * parent) : QTcpServer(parent)
{
}
SslServer::~SslServer()
{
}
void SslServer::incomingConnection(qintptr socketDescriptor)
{
    //Создаем новый SSL-сокет
    QSslSocket *serverSocket = new QSslSocket;
    QSslConfiguration config;
    //Определяем поддерживаемые сервером шифронаборы
    QList<QSslCipher> cipherList = serverSocket->supportedCiphers();
    //Удаляем из списка небезопасные сертификаты
    for (int i = 0; i < cipherList.size(); i++){
        if ((cipherList[i].authenticationMethod() == "NULL") ||
                (cipherList[i].encryptionMethod() =="NULL") ||
                (cipherList[i].keyExchangeMethod() == "NULL")){
            qDebug() << "Deleted" << cipherList[i].name();
            cipherList.removeAt(i);
        }
    }
    //Задаем новый список шифронаборов в конфигурации
    config.setCiphers(cipherList);
    //Применяем конфигурацию к новому соединению
    serverSocket->setSslConfiguration(config);
    //Если дескриптор сокета успешно выдан ОС
    if (serverSocket->setSocketDescriptor(socketDescriptor)) {
        //Можно начинать процесс хендшейка
        serverSocket->setLocalCertificate(m_sslLocalCertificate);
        serverSocket->setPrivateKey(m_sslPrivateKey);
        serverSocket->setProtocol(m_sslProtocol);
        serverSocket->startServerEncryption();
    }
    else {
        qDebug() << __FUNCTION__ << "Error in socketDescriptor";
        delete serverSocket;
    }
    addPendingConnection(serverSocket);
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
bool SslServer::setSslPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm, QSsl::EncodingFormat
                                 format, const QByteArray &passPhrase)
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
