#pragma once

#include "stdafx.h"

class DBPresenter:IPresenter
{
protected:
    QString m_nameDB;

    QSqlDatabase m_db; // база данных
    QSqlQuery* m_query;

    Request m_req;

    QString m_tabUsers;

public:
    DBPresenter();

    virtual ~DBPresenter();


     virtual void createConnection();
     virtual void createTables()=0;
     virtual void insertUser(User)=0;

};

