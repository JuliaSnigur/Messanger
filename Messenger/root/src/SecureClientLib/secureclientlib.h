#pragma once

#include"stdafx.h"

class SecureClient: public QObject
{
    Q_OBJECT
private:

    QSslSocket* m_Client;
    quint16     m_nNextBlockSize;

public:
    SecureClient(QObject* obj=0);
    ~SecureClient();


    void createConnection(const QString& strHost, int nPort);

private slots:

    /*
    void onConnected();
       void onTextMessageReceived(QString message);

       */
       void slotError       (QAbstractSocket::SocketError);



/*


private slots:
    void slotReadyRead   ( );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   ();
    void slotSendToServer(const QString& message);
    void slotSslErrors(const QList<QSslError> &errors);

signals:
    void signalInsertUserIntoTabSession();
    void signalGetListsClients(QVector<int> vector);
    void signalGetID(int id);
    void signalSendMessage();
    */

};

