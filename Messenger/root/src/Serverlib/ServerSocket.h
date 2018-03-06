#pragma once

class QTcpServer;
class QTcpSocket;



#include"DBLib/user.h"
#include"DBLib/request.h"
#include"DBLib/ipresenter.h"
#include"DBLib/dbpresenter.h"
#include "DBLib/dbserverpresenter.h"


namespace ServerNamespace {


class ServerSocket : public QObject
{
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;

    quint16     m_nNextBlockSize;// block's lenghth

    QHash<int,QTcpSocket*> m_hash;

    DBServerPresenter m_db;

    QTcpSocket* m_ClientSocket;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void sendToAllClients( const QString& str);


public:
    ServerSocket(QObject*pwgt=0);
    ServerSocket(int nPort, QObject* pwgt = 0);

    virtual~ServerSocket();


    void createServer(int port);

    void registration(QString&);
    void authorization(QString&);
    void sendList();
  //  void message(QString&);
 void message(QString&);


 void threadHandler();


public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
            void slotDisconnect();

};

}
