#pragma once

#include <QObject>
#include <QSslSocket>
#include <QFile>



#include"user.h"
#include"dbpresenter.h"
#include"dbclientpresenter.h"


namespace Client {



    class ClientConnection : public QObject
    {
        Q_OBJECT
    private:
        std::shared_ptr<QSslSocket> m_client;
        DB::DBClientPresenter m_db;
        QHash<int,QString> m_hash;

        QString m_fileName;
        User m_user;
        int m_idFriend;
        int m_idDialog;


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



    };


}
