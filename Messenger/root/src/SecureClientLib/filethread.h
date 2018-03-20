#pragma once

#include <QThread>
#include <QFile>
#include <QSslSocket>


namespace Client {



    class FileThread: public QThread
    {
    public:
        FileThread( std::shared_ptr<QSslSocket> client, const QString& fileName, QObject *parent = 0);
        virtual ~FileThread();

        void run();


    private:
        QFile m_file;
        QString m_fileName;
        std::shared_ptr<QSslSocket> m_client;


    };

}
