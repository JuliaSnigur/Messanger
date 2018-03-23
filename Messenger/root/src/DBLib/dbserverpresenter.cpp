#include "stdafx.h"

#include"request.h"
#include"user.h"
#include"dbpresenter.h"

#include "dbserverpresenter.h"

DB::DBServerPresenter::DBServerPresenter()
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

DB::DBServerPresenter::DBServerPresenter(const QString &nameDB)
{
    m_nameDB = nameDB;
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

DB::DBServerPresenter::~DBServerPresenter(){}


 void DB::DBServerPresenter::createTables()
 {
     // users
     QString params="id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE,password TEXT, status INTEGER";
     QString str=Request::createTable(m_tabUsers,params);

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


 bool DB::DBServerPresenter::insertUser(const User& us)
 {
     QString params = "login, password, status";
     QString values = "'%1','%2', %3";

     QString str_insert = Request::insertData(m_tabUsers,params,values);
     QString str = str_insert.arg(us.getLogin()).arg(us.getPassword()).arg(us.getStatus());

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


 User* DB::DBServerPresenter::searchUser(const QString& log)
 {
     User* us = nullptr;
     QString params = '*';
     QString values = "login = '" + log + "'";
     QString str = Request::searchData(m_tabUsers,params,values);

       m_query->exec(str);
       if(m_query->next())
       {
          us=new User(log);
          us->setID( m_query->value(0).toInt());
          us->setPassword(m_query->value(2).toString());
          us->setStatus(m_query->value(3).toInt());

          qDebug() << "The data search";
          return us;
       }
       else
          qDebug() << "The data dosn't search";

       return nullptr;
 }

 int DB::DBServerPresenter::searchID(const QString& log)
 {
     QString params = "id";
     QString values = "login = '" + log + "'";
     QString str = Request::searchData(m_tabUsers, params, values);

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

 QString DB::DBServerPresenter::searchLogin(const int& id)
 {

     QString params = "login";
     QString values = "id=" + QString::number(id);
     QString str = Request::searchData(m_tabUsers, params, values);

       m_query->exec(str);
       if(m_query->next())
          {
              qDebug()<<"The data search";
              return m_query->value(0).toString();
          }
          else
           qDebug()<<"The data doesn't search";

       return "";
 }

 bool DB::DBServerPresenter::searchStatus(const int& id)
 {
     bool res;
     QString params = "status";
     QString values = "id=" + QString::number(id);
     QString str = Request::searchData(m_tabUsers, params, values);

       m_query->exec(str);
       if(m_query->next())
          {
              qDebug() << "The data search";
              res = m_query->value(0).toInt();
              return res;
          }
          else
           qDebug()<<"The data doesn't search";

      throw std::exception("The user doesn't exist");
 }


QVector<User *> DB::DBServerPresenter::getListOfUser()
{
    User* us = nullptr;
    QVector<User*> vec;
    QString params = '*';
    QString str = Request::searchAllData(m_tabUsers, params);

      m_query->exec(str);

      while(m_query->next())
      {
          us = new User(m_query->value(0).toInt(), m_query->value(1).toString(), m_query->value(3).toInt());
          vec.push_back(us);
      }
      return vec;
}

bool DB::DBServerPresenter::updateStatus(const int& id, const bool& status)
{
    try
    {
        QString params = "status = " + QString::number(status);
        QString values = "id = " + QString::number(id);
        QString str = Request::updateData(m_tabUsers, params, values);
        if( m_query->exec(str))
        {
           qDebug()<<"The data update";
           return true;
        }
    }
    catch(const std::exception& ex)
    {
        qDebug() << ex.what();
    }
    return false;
}
