#pragma once

#include"stdafx.h"


#include"request.h"
#include "user.h"
#include"ipresenter.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

namespace ClientNamespace {


class ClientSocket: public QObject
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока
    DBClientPresenter m_db;

    User m_user;

    QFile* file;



    void sendToServer(const QString&);

public:
    ClientSocket(QObject* parent=0);
    virtual ~ClientSocket();


    void registration(const QString& login,const QString& pass);
    void authorization(const QString& login,const QString& pass);
    void sendMessage(const QString& mess);

    void createConnection(const QString& strHost, int nPort);

/*
    void sendFile(const QString&);
    void receiveFile(QString fileName);
    void receiveFile();
*/


private slots:
    void slotReadyRead   ( );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();
   // void sendPartOfFile();

signals:
    void signalInsertUserIntoTabSession();
    void signalGetListsClients(QVector<int>);
    void signalGetID(int);
    void signalSendMessage();

};

}
