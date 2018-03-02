#pragma once

#include"stdafx.h"

class MyClient: public QObject
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока

    QFile* file;




public:
    MyClient(QObject* parent=0);
    virtual ~MyClient();


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


};

