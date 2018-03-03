#include "stdafx.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"

#include "dbserverpresenter.h"


DBServerPresenter::DBServerPresenter()
{
    m_nameDB="Server_db.db";
    m_tabUsers="users";

    try{
        createConnection();
        createTables();
    }
    catch(std::exception& ex)
    {
        qDebug()<<ex.what();
    }



}

DBServerPresenter::~DBServerPresenter(){}



/*
    Создание таблицы User
    Атрибуты: id, login,password
    Возвращает: true -созданную таблицу, false - сообщение об ошибке
*/
 void DBServerPresenter::createTables()
 {
     // users
     QString params="id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE,password TEXT";
     QString str=m_req.createTable(m_tabUsers,params);

     if(!m_query->exec(str))
     {
            qDebug() << "DataBase: error of create " <<m_tabUsers;
            qDebug() << m_query->lastError().text();
     }
    else
         qDebug()<<"The table "<<m_tabUsers<<" is creating";
 }


 /*
     Вставка юзера в БД
     Атрибуты: User& us - объект юзера
     Возвращает: true -юзер добавлен, false - сообщение об ошибке
 */
 void DBServerPresenter::insertUser(User us)
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

  User DBServerPresenter::searchUser(const int id)
  {
      User us;
      QString params='*';
      QString values="id="+QString::number(id);
      QString str=m_req.searchData(m_tabUsers,params,values);

        m_query->exec(str);
        if(m_query->next())
           {

               us.setID( m_query->value(0).toInt());
               us.setLogin( m_query->value(1).toString());
               us.setPassword(m_query->value(2).toString());
               qDebug()<<"The data search";

           }
           else
            qDebug()<<"The data dosn't search";

        return us;
  }

 User DBServerPresenter::searchUser(const QString& log)
 {
     User us;
     QString params="id,login,password";
     QString values="login = '"+log+"'";
     QString str=m_req.searchData(m_tabUsers,params,values);

       m_query->exec(str);
       if(m_query->next())
          {

              us.setID( m_query->value(0).toInt());
              us.setLogin( m_query->value(1).toString());
              us.setPassword(m_query->value(2).toString());
              qDebug()<<"The data search";
          }
          else
          qDebug()<<"The data dosn't search";

       return us;
 }

 int DBServerPresenter::searchID(const QString& log)
 {
     QString params="id";
     QString values="login = '"+log+"'";
     QString str=m_req.searchData(m_tabUsers,params,values);

       m_query->exec(str);
       if(m_query->next())
          {
              qDebug()<<"The data search";
              return m_query->value(0).toInt();
          }
          else
          qDebug()<<"The data dosn't search";

       return -1;
 }

 QString DBServerPresenter::searchLogin(const int& id)
 {

     QString params="login";
     QString values="id="+QString::number(id);
     QString str=m_req.searchData(m_tabUsers,params,values);

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


