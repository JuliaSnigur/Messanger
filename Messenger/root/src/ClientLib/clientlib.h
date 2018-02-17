#include "stdafx.h"

#include <QWidget>

#include<QTcpSocket>
#include<QTcpServer>

#include <QTextEdit>
#include <QLineEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLabel>
#include<QTime>

#ifndef CLIENTLIB_H
#define CLIENTLIB_H


class MyClient : public QWidget
{
Q_OBJECT
private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;// необходимый для хранения длины следующего полученного от сокета блока

public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0) ;

private slots:
    void slotReadyRead   ( );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected   ();
};
#endif // CLIENTLIB_H
