#pragma once

//#include"stdafx.h"
#include "stable.h"



class MyClient:public QObject
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    QString  m_ptxtInput;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока

public:
    MyClient(const QString& strHost, int nPort,QObject* parent=0) ;

     void sendToServer(const User& str);

private slots:
    void slotReadyRead   ( );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();
};

