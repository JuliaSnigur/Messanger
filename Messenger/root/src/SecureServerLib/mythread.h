#pragma once

#include <QThread>
#include <QSslSocket>
#include <QDebug>
#include <QFile>

#include <QMutex>
#include <QPointer>


#include "user.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"


namespace Server {

    class MyThread : public QThread
    {
        Q_OBJECT
    public:
         MyThread(qintptr id, std::shared_ptr<DB::DBServerPresenter> db, std::shared_ptr<QHash<int,QSslSocket*>> hash, QObject *parent = 0);

         virtual ~MyThread();

        void run();
        bool sendToClient(QSslSocket* m_sslClient, const QString& str);

        void registration(QString& str);
        void authorization(QString& str);
        void sendList();
        void message(QString& str);
        void receiveFile(const QString& fileName);

    public slots:
        void slotReadyRead();
        void slotDisconnect();
        void slotReceiveFile();


    signals:
        void error(const QAbstractSocket::SocketError& errors);


    private:
        std::shared_ptr<QSslSocket> m_sslClient;
        qintptr m_socketDescriptor;
        QMutex m_mutexDB,m_mutexHashTab;
        QFile m_file;
        ulong    m_sizeReceiveFile;

        std::shared_ptr<DB::DBServerPresenter> m_db;
        std::shared_ptr<QHash<int,QSslSocket*>> m_hash;


    };

}
