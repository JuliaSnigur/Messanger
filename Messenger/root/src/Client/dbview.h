#pragma once
#include"stdafx.h"

class DBView: public IDBView
{
private:
   // static DBView* instance;


protected:
    DBClientPresenter m_dbPres;
public:

    DBView();

    virtual ~DBView();
/*
    static DBView* getInstance()
    {
       if (instance == nullptr)
            instance = new DBView();

       return instance;
    }
*/
    virtual void createConnection();
    virtual void createTables();

     virtual void insertUsers(User&);


};
