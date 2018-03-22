#pragma once

#include <QObject>
#include <QSslSocket>
#include <QFile>
#include <QSslKey>



#include "user.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"


namespace Client {
    class ClientConnection : public QObject
    {
        Q_OBJECT

    void sendToServer(const QString& message);

    public:
        ClientConnection(QObject *parent = 0);
        virtual ~ClientConnection();

        void sendFile(const QString& filename);
        void getFile();


    public slots:

       void slotEncrypted();
       void slotReadyRead();
       void sslError( QList<QSslError> errors );
       void slotDisconnect();

       void slotConnection(const QString& hostName, const int& port);
       void slotRegistration(const QString& login, const QString& pass);
       void slotAuthorization(const QString& login, const QString& pass);
       void slotGetListFriend();
       void slotChoiceFriend(const int &id);
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

        User m_user;
        int m_idFriend;
        int m_idDialog;

        QString m_fileName;

        QSslCertificate m_certSever;
        QSslCertificate m_certClient;
        QSslKey m_key;

    };


}
