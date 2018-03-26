#pragma once

#include <QObject>
#include <QSslSocket>
#include <QFile>
#include <QMutex>

#include "DataLib/user.h"
#include "DBLib/dbpresenter.h"
#include "DBLib/dbclientpresenter.h"
#include "filethread.h"

namespace Client {
    class ClientConnection : public QObject
    {
        Q_OBJECT
    public:
        ClientConnection(QObject *parent = 0);
        virtual ~ClientConnection();

        void sendFile(const QString& filename);
        const QString variable(QString& str);
        void sendToServer(const QString& message);

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
       void slotSendFile(const QString& path);
       void slotError(const QString& error);

    signals:
       void signalSendRespond(const QString& res);
       void signalSendListClients(const QString& res);
       void signalGetID(int);
       void signalSendInfo();
       void signalSendDialog(QQueue<QString> q);
       void signalSendFileBlock();

    private:
        std::shared_ptr<QSslSocket> m_client;
        std::shared_ptr<FileThread> m_thread;
        DB::DBClientPresenter m_db;
        Data::User m_user;
        int m_idFriend;
        int m_idDialog;
        QByteArray m_certServer;
    };
}
