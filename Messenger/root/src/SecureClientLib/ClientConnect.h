#pragma once

#include <QObject>
#include <QSslSocket>
#include <QFile>



#include "user.h"
#include"idbpresenter.h"
#include"dbclientpresenter.h"


namespace Client {



    class ClientConnection : public QObject
    {
        Q_OBJECT

    void sendToServer(const QString& message);

    public:
        ClientConnection(QObject *parent = 0);

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
       void slotSendFile(const QString& filename);


    signals:


       void signalSendRespond(const QString& res);
       void signalSendListClients(const QString& res);

        void signalGetID(int);
        void signalSendInfo();
        void signalSendDialog(QQueue<QString> q);

    private:
        std::shared_ptr<QSslSocket> m_client;
        DB::DBClientPresenter m_db;
        QHash<int,QString> m_hash;

        User m_user;
        int m_idFriend;
        int m_idDialog;

        QString m_fileName;
        QString m_clientKey;
        QString m_certServer;
        QString m_certClient;

    };


}
