#pragma once


class UsersTable: public TableDataBase
{
protected:

public:
    UsersTable();
    UsersTable(QString);

    virtual ~UsersTable();

     virtual QString createTable();
     virtual QString insertData();
     virtual QString searchData(QString);
     virtual QString updateData(int);
};

