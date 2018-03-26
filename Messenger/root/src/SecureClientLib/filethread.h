#pragma once

#include <QThread>
#include <QFile>
#include <QSslSocket>


namespace Client {
    class FileThread: public QThread
    {
         Q_OBJECT
    public:
        FileThread(QObject *parent = 0);
        virtual ~FileThread();
        void run();
        void setInfo(std::shared_ptr<QSslSocket> client, const QString& fileName);

    signals:
        void signalError(const QString& error );

    public slots:
        void sendFileBlock();

    private:
        std::shared_ptr<QFile> m_file;
        std::shared_ptr<QSslSocket> m_client;
    };
}
