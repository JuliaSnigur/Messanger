#pragma once

#include<QTcpServer>
#include<QSslSocket>

#include"DBLib/user.h"
#include"DBLib/request.h"
#include"DBLib/ipresenter.h"
#include"DBLib/dbpresenter.h"
#include "DBLib/dbserverpresenter.h"

class SecureServer:public QTcpServer
{
Q_OBJECT

private:

    QSslSocket* m_Server;
    QSslSocket* m_Client;

    quint16     m_nNextBlockSize;// block's lenghth

    QHash<int,QTcpSocket*> m_hash;

    DBServerPresenter m_db;

    void incomingConnection(int handle);

public:
    SecureServer();
    ~SecureServer();

    void createServer(int port);

private slots:

    void slotNewConnection();
    void slotEcrypted();
    void slotSslError(const QList<QSslError> &errors);
    void slotDisconnect();
    void slotReadClient();


};

