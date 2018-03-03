#pragma once
/*
#include "stdafx.h"

#include"request.h"
#include "user.h"
#include"ipresenter.h"
#include "dbpresenter.h"
#include "dbserverpresenter.h"


#include"ServerSocket.h"

using namespace ServerNamespace;

*/

class Server:public QObject
{
Q_OBJECT
private:
    DBServerPresenter m_db;
    std::vector<int> vecCostumers; // vector users id
    ServerSocket m_server;



public:
    Server(QObject* obj=0);
    virtual ~Server();


    void startWork();

public slots:
    void slotInsertUserIntoDB(const User&);
    void slotActivateUser(const QString&);

};

