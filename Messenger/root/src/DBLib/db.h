#pragma once

class DB
{
protected:
    QString m_nameBase;//имя базы данных
    QSqlDatabase m_db; // база данных
    QSqlQuery* m_query;
public:
    DB();
    DB(QString);

     bool createConnection();
     virtual bool createTable()=0;

     virtual void insertData(User&)=0;
     virtual  User* userSearchID(int id)=0;
     virtual  User* userSearchLoginPassword(string,string)=0;
     virtual  User* userSearchLogin(string)=0;
     virtual bool updateStatus(int id)=0;
};

