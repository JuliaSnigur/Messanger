#include "stdafx.h"
#include "dbserverpresenter.h"

DBServerPresenter::DBServerPresenter()
{
    m_nameDB="Server_db.db";
    m_tabUsers="users";
}

DBServerPresenter::~DBServerPresenter(){}




 void DBServerPresenter::createTables()
 {
     // users
     QString params="id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE,password TEXT,status INTEGER";
     QString str=m_req.createTable(m_tabUsers,params);

     if(!m_query->exec(str))
     {
            qDebug() << "DataBase: error of create " <<m_tabUsers;
            qDebug() << m_query->lastError().text();
     }
     qDebug()<<"The table "<<m_tabUsers<<" is creating";
 }

 void DBServerPresenter::insertUser(User& us)
 {
     QString params="login, password";
     QString values="'%1','%2'";

     QString str_insert=m_req.insertData(m_tabUsers,params,values);
     QString str=str_insert.arg(us.getLogin()).arg(us.getPassword());

     if (!m_query->exec(str))
         qDebug() << "Unable to make insert operation";
     else
         qDebug() << "To make insert operation";

 }
