#pragma once


#include <QThread>
#include <QSslSocket>
#include <QDebug>
#include <QFile>

#include <QMutex>
#include <QPointer>

#include "DataLib/user.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"

namespace Server {
class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(qintptr id,  std::shared_ptr<DB::DBServerPresenter> db,   std::shared_ptr<QHash<int,QSslSocket*>> hash, QObject *parent = 0);
    // нужен ли деструктор ?
    void run();
    bool sendToClient(QSslSocket* m_sslClient, const QString& str);
    void notificateClients();
    void registration(QString& str);
    void authorization(QString& str);
    void sendList();
    void message(QString& str);
    void receiveFile(const QString& fileName);
    QByteArray encryptedPassword(const QString& pass);

public slots:
    void slotReadyRead();
    void slotDisconnect();
    void slotReceiveFile();
signals:
    void error(const QAbstractSocket::SocketError& error);

private:
    std::shared_ptr<QFile> m_file;
    qint64 m_sizeReceiveFile;
    qintptr m_socketDescriptor;
    QMutex m_mutexDB;
    QMutex m_mutexHashTab;
    std::shared_ptr<QSslSocket> m_sslClient;
    std::shared_ptr<DB::DBServerPresenter> m_db;
    std::shared_ptr<QHash<int,QSslSocket*>> m_hash;
    QByteArray m_serverKey;
    QByteArray m_certServer;
    QByteArray m_certClient;
};
}
