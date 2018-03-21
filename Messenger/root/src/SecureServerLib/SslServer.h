#pragma once


#include <QTcpServer>
#include <QString>
#include <QSsl>
#include <QSslCertificate>
#include <QSslKey>
#include<QSslSocket>
#include<QPointer>

#include "user.h"
#include "idbpresenter.h"
#include "dbserverpresenter.h"

#include "mythread.h"


namespace Server {



class SslServer : public QTcpServer
{
    Q_OBJECT

public:
    SslServer(QObject *parent = 0);

    void start(const int& port);

public slots:
     void slotSslError(const QAbstractSocket::SocketError& errors);

protected:
    void incomingConnection(qintptr socketDescriptor) override final;

private:
     std::shared_ptr<QHash<int, QSslSocket*>> m_hash;
     std::shared_ptr<DB::DBServerPresenter> m_db;

     QPointer<MyThread> thread;
};

}
