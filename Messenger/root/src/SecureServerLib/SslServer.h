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

    void start(const int& port);

signals:
    void signalStartThread();

public slots:
     void slotSslError(const QAbstractSocket::SocketError& errors);
     void slotFinished();

protected:
    void incomingConnection(qintptr socketDescriptor) override final;


private:

    QSslSocket *sslSocket ;

    QHash<int,QSslSocket*>* m_hash;
    DBServerPresenter* m_db;

    int m_countThread;
    int m_maxCountThreads;

    qintptr m_socketDescriptor;
};

