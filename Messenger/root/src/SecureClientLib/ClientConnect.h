#pragma once

#include <QObject>
#include<QSslSocket>

#include"stdafx.h"


#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbclientpresenter.h"




class ClientConnection : public QObject
{
    Q_OBJECT
private:
    QPointer<QSslSocket> m_client;
    DBClientPresenter m_db;
    User m_user;
    int m_idFriend;
    int m_idDialog;


void sendToServer(const QString& message);

public:
    ClientConnection(QObject *parent = 0);
    virtual~ClientConnection();

   // void start(const QString& hostName,int port);

   // void slotRegistration(const QString& login,const QString& pass);
   // void slotAuthorization(const QString& login,const QString& pass);
    void sendMessage(const QString& mess);
    void setIdFriend(int id);
    void sendFile(const QString& filename);
    void getFile();
    void showDialog();

public slots:

   void slotEncrypted();
   void slotReadyRead();
   void sslError( QList<QSslError> errors );
   void slotDisconnect();

    void slotConnection(const QString& hostName,int port);
   void slotRegistration(const QString& login,const QString& pass);
   void slotAuthorization(const QString& login,const QString& pass);


signals:


   void signalSuccessful(int num);

    void signalGetListsClients(QVector<int>);
    void signalGetID(int);
    void signalSendMessage();
    void signalSendInfo();

    void signalError(const QString&);

};


