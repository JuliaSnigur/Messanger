#pragma once


class DBPresenter:IPresenter
{
protected:
    QString m_nameDB;

    QSqlDatabase m_db; // база данных
    QSqlQuery* m_query;

    Request m_req;

    QString m_tabUsers;

    virtual void createConnection();
    virtual void createTables()=0;

public:
    DBPresenter();

    virtual ~DBPresenter();


     virtual void insertUser(User)=0;

};

