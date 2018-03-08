#pragma once


#include <QObject>
#include<QSslSocket>

class ClientConnection : public QObject
{
    Q_OBJECT
private:
    QSslSocket* m_client;


public:
    ClientConnection(QObject *parent = 0);
    virtual~ClientConnection();

    void start(const QString& hostName,int port);

    void sendToServer(const QString& message);

public slots:
    void run();

   void slotEncrypted();
   void slotErrors(const QList<QSslError> &errors);
   void slotReadyRead();

signals:
    void signalInsertUserIntoTabSession();
    void signalGetListsClients(QVector<int>);
    void signalGetID(int);
    void signalSendMessage();
    void signalSendInfo();

};


