#pragma once


#include <QSqlDatabase>
#include <QSqlQuery>

#include"ipresenter.h"
#include<DBLib/request.h>



class DBPresenter:IPresenter
{
protected:
    QString m_nameDB;

    QSqlDatabase m_db; // база данных
    QSqlQuery* m_query;

    Request m_req;



    virtual void createConnection();
    virtual void createTables()=0;

public:
    DBPresenter();

    virtual ~DBPresenter();

};

