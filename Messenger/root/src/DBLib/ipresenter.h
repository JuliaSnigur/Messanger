# pragma once


class IPresenter
{
    virtual void createConnection()=0;
    virtual void createTables()=0;

    virtual void insertUser(User)=0;
};
