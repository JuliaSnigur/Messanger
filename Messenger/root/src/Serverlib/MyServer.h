#pragma once
#include "stdafx.h"
#include "SSLServerLib/SSLServerLib.h"
#include <QDialog>
#include <QSslConfiguration>
#include <QSslCipher>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QtSql/QSqlError"
class QTcpServer;
class QTextEdit;
class QTcpSocket;

// ======================================================================
class MyServer : public QWidget {
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;//длина следующего полученного от сокета блока

    //ssl подключение
    SslServer * SSLServer = 0;
    QSslSocket * sslConn = 0;
    QList<QTcpSocket*> ClientList;
    int i = 0;
    QListWidget * listForAccept;
    Q_SLOT int startServer(bool checked);
    Q_SLOT void updateStatus();
    Q_SLOT void acceptConnection();
    Q_SLOT void readMessage();
    Q_SLOT int showNewClientsList();
    Q_SLOT int acceptNewClients(QModelIndex);
//    int connectDB();
//    int createDB();
//     QSqlDatabase db;
    QMap<QString, QSslSocket *> ClientsList;
    QMap<int, QSslSocket *> SClients;
    QVector<QSslSocket*> sslList;
    int getTypeOfMess(QByteArray & message, QSslSocket * sslConn);
    void registerQuery(QByteArray & message);
    void loginQuery(QByteArray & message, QSslSocket * sslConn);
    int getMessage(QByteArray & message);
    int sendMessage(QString & to, QString & from, QString & text, QByteArray & message);
    int addClientQuery(QByteArray & message, QSslSocket * sslConn);
    int setNewConnection(QSslSocket * sslConn);
    int addClient(QByteArray & message);
    int logOff(QByteArray & message, QSslSocket * sslConn);

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    MyServer(int nPort, QWidget* pwgt = 0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};

