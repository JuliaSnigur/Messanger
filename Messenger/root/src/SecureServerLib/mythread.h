#pragma once

#include <QThread>
#include <QSslSocket>
#include <QDebug>

#include <QMutex>
#include <QPointer>


#include "user.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"


class MyThread : public QThread
{
    Q_OBJECT
public:
     MyThread(qintptr id, DB::DBServerPresenter* db, QHash<int,QSslSocket*>* hash, QObject *parent = 0);

    void run();
    bool sendToClient(QSslSocket* m_sslClient, const QString& str);

    void registration(QString& str);
    void authorization(QString& str);
    void sendList();
    void message(QString& str);

public slots:
    void slotReadyRead();
    void slotDisconnect();

signals:
    void error(const QAbstractSocket::SocketError& errors);


private:
    std::shared_ptr<QSslSocket> m_sslClient;
    qintptr m_socketDescriptor;
    QMutex m_mutexDB,m_mutexHashTab;

    std::shared_ptr<DB::DBServerPresenter> m_db;
    QHash<int,QSslSocket*>* m_hash;


};
