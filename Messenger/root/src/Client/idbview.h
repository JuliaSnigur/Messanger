#pragma once

class IDBView
{
    virtual void createConnection()=0;

    virtual void createTables()=0;
    virtual void insertUsers(User&)=0;
    virtual User* searchUsers(const QString)=0;

};
