#pragma once

#include <QObject>
#include<QSslSocket>

#include"stdafx.h"


#include"user.h"
#include"dbpresenter.h"
#include"dbclientpresenter.h"




class ClientConnection : public QObject
{
    Q_OBJECT
private:
    QPointer<QSslSocket> m_client;
    DB::DBClientPresenter m_db;
    QHash<int,QString> m_hash;

    User m_user;
    int m_idFriend;
    int m_idDialog;


void sendToServer(const QString& message);

public:
    ClientConnection(QObject *parent = 0);
    virtual~ClientConnection();


    void sendFile(const QString& filename);
    void getFile();


public slots:

   void slotEncrypted();
   void slotReadyRead();
   void sslError( QList<QSslError> errors );
   void slotDisconnect();

    void slotConnection(const QString& hostName,int port);
   void slotRegistration(const QString& login,const QString& pass);
   void slotAuthorization(const QString& login,const QString& pass);
   void slotGetListFriend();
   void slotChoiceFriend(const QString& login);
   void slotSendMessage(const QString& message);


signals:


   void signalSendRespond(QString res);
   void signalSendListClients(QString& res);

    void signalGetID(int);
   // void signalSendMessage();
    void signalSendInfo();
    void signalSendDialog(QQueue<QString> q);



};


