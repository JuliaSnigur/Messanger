#pragma once

#include "stdafx.h"

class MyClient: public QObject
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    QString  m_ptxtInput;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока

public:
    MyClient(QObject* parent=0);
    virtual ~MyClient();


    void createConnection(const QString& strHost, int nPort);
    void sendToServer( QString&,QString&);


private slots:
    void slotReadyRead   ( );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();



};

