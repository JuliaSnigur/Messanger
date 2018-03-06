#pragma once

#include"stdafx.h"


namespace ClientNamespace {


class ClientSocket: public QObject
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока

    QFile* file;






public:
    ClientSocket(QObject* parent=0);
    virtual ~ClientSocket();


    void sendToServer(const QString&);
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
