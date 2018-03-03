#include "stdafx.h"

#include"request.h"
#include"user.h"
#include"ipresenter.h"
#include"dbpresenter.h"
#include "dbclientpresenter.h"



DBClientPresenter::DBClientPresenter()
{
    this->m_nameDB="Client_db.db";

    m_tabUsers="users";
    m_tabDialogs="dialogs";
    m_tabMessages="messangers";


    try{
        createConnection();
        createTables();
    }
    catch(std::exception& ex)
    {
        qDebug()<<ex.what();
    }


}

DBClientPresenter::~DBClientPresenter(){}


  void DBClientPresenter::createTables()
  {
      // users
      QString params="id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE";
      QString str=m_req.createTable(m_tabUsers,params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " <<m_tabUsers;
             qDebug() << m_query->lastError().text();
      }
      qDebug()<<"The table "<<m_tabUsers<<" is creating";

      //dialogs
       params="id INTEGER PRIMARY KEY AUTOINCREMENT,idSender INTEGER,idReceiver INTEGER ";
       str=m_req.createTable(m_tabDialogs,params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabDialogs;
             qDebug() << m_query->lastError().text();
      }
      qDebug()<<"The table "<<m_tabDialogs<<" is creating";

      //messanges
       params="id INTEGER PRIMARY KEY AUTOINCREMENT,messange TEXT,idDialogs INTEGER ";
       str=m_req.createTable(m_tabMessages,params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabMessages;
             qDebug() << m_query->lastError().text();
      }
      else
        qDebug()<<"The table "<<m_tabMessages<<" is creating";

  }


   void DBClientPresenter::insertUser(User us)
   {
       QString params="login";
       QString values="'%1'";

       QString str_insert=m_req.insertData(m_tabUsers,params,values);
       QString str=str_insert.arg(us.getLogin());

       if (!m_query->exec(str))
           qDebug() << "Unable to make insert operation";
       else
           qDebug() << "To make insert operation";

   }
