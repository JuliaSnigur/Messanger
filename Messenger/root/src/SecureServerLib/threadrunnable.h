#pragma once

#include<QRunnable>
#include<QSslSocket>
#include<QMutex>

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include"dbserverpresenter.h"

class ThreadRunnable:public QObject, public QRunnable
{
    Q_OBJECT
private:

     QSslSocket* m_sslClient;
     QMutex m_mutexDB,m_mutexHashTab;

    static QHash<int,QSslSocket*> m_hash;
    static DBServerPresenter m_db ;
    qintptr m_socketDescriptor;


protected:
    void run();


public:
    ThreadRunnable(qintptr socketDescriptor,QObject* obj=0);

    virtual ~ThreadRunnable();


    void sendToClient(QSslSocket* socket,const QString& str);

    void registration(QString& str);
    void authorization(QString& str);
    void sendList();
    void message(QString& str);

public slots:

    void slotReadyRead();
    void slotDisconnect();
    void slotSslError(QList<QSslError> errors);



};

