#pragma once
#include"stdafx.h"
class ServerDB: public DB
{
protected:
    TableDataBase* m_tableUsers;
public:
    ServerDB();
    ServerDB(QString);

    ~ServerDB();

   virtual bool createTable();

   virtual void insertData( User&);
   virtual  User* userSearchID(int id);
   virtual  User* userSearchLoginPassword(string,string);
   virtual  User* userSearchLogin(string);
    virtual bool updateStatus(int id);
};
