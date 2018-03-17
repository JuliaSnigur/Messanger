#include "stdafx.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"

#include "dbserverpresenter.h"


DBServerPresenter::DBServerPresenter()
{
    m_nameDB = "Server_db.db";
    m_tabUsers = "users";

    try{
        createConnection();
        createTables();
    }
    catch(const std::exception& ex)
    {
        qDebug() << ex.what();
    }
}

DBServerPresenter::~DBServerPresenter(){}


 void DBServerPresenter::createTables()
 {
     // users
     QString params="id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE,password TEXT";
     QString str=m_req.createTable(m_tabUsers,params);

     if(m_query->exec(str))
     {
         qDebug()<<"The table "<<m_tabUsers<<" is creating";

     }
    else
     {
         qDebug() << "DataBase: error of create " <<m_tabUsers;
         qDebug() << m_query->lastError().text();
     }
 }


 bool DBServerPresenter::insertUser( User us)
 {
     QString params = "login, password";
     QString values = "'%1','%2'";

     QString str_insert = m_req.insertData(m_tabUsers,params,values);
     QString str = str_insert.arg(us.getLogin()).arg(us.getPassword());

     if (m_query->exec(str))
     {
         qDebug() << "To make insert operation";
         return true;
     }
     else
     {
         qDebug() << "Unable to make insert operation";
         return false;
     }
 }


 User* DBServerPresenter::searchUser(const QString& log)
 {
     User* us;
     QString params = '*';
     QString values = "login = '" + log + "'";
     QString str = m_req.searchData(m_tabUsers,params,values);

       m_query->exec(str);
       if(m_query->next())
       {
          us=new User(log);
          us->setID( m_query->value(0).toInt());
          us->setPassword(m_query->value(2).toString());

          qDebug() << "The data search";
          return us;
       }
       else
          qDebug() << "The data dosn't search";

       return nullptr;
 }

 int DBServerPresenter::searchID(const QString& log)
 {
     QString params = "id";
     QString values = "login = '" + log + "'";
     QString str = m_req.searchData(m_tabUsers, params, values);

       m_query->exec(str);
       if(m_query->next())
          {
              qDebug()<<"The data search";
              return m_query->value(0).toInt();
          }
          else
          qDebug()<<"The data dosn't search";

       return 0;
 }

 QString DBServerPresenter::searchLogin(const int& id)
 {

     QString params = "login";
     QString values = "id=" + QString::number(id);
     QString str = m_req.searchData(m_tabUsers, params, values);

       m_query->exec(str);
       if(m_query->next())
          {
              qDebug()<<"The data search";
              return m_query->value(0).toString();
          }
          else
           qDebug()<<"The data dosn't search";

       return "";
 }


