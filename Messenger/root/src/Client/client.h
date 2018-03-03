#pragma once

#include"stdafx.h"


#include"request.h"
#include "user.h"
#include"ipresenter.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

#include"guilib.h"
#include"ClientSocket.h"

using namespace ClientNamespace;


class Client: public QObject
{

  Q_OBJECT
private:
    DBClientPresenter
    m_db;
    GuiLib m_gui;
    ClientSocket m_client;
    User m_us;

    QVector<int> m_vecClients;

    bool m_isStartDialog;

public:
    Client(QObject* obj=0);

   virtual ~Client();


    void startWork();

    void dialog();

public slots:
    void slotAuthorization(QString,QString);
    void slotConnection(QString,QString);
    void slotRegistration(QString,QString);
    void slotHello();


    void slotInsertUserIntoTabSession();
    void slotGetListsClients(QVector<int>);
    void slotGetID(int);
};

