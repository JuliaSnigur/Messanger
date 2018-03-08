#pragma once

#include <QObject>
#include<QSslSocket>


#include"SslServer.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"

class ServerConnection : public QObject
{
    Q_OBJECT
private:
     SslServer* m_sslServer;
     QSslSocket * m_sslClient;

     QHash<int,QSslSocket*> m_hash;
     DBServerPresenter m_db;



     void sendToClient(QSslSocket* pSocket, const QString& str);
     void sendToAllClients( const QString& str);



public:
    ServerConnection(QObject *parent = 0);

    void registration(QString& str);
    void authorization(QString& str);
    void sendList();
    void message(QString& str);

 void start(int port);


public slots:
    void run();

    void slotConnection();
    void slotReadyRead();
    void slotDisconnect();
    //void slotEncrypted();

};