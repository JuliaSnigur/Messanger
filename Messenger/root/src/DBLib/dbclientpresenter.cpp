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
}

DBClientPresenter::~DBClientPresenter(){}

DBClientPresenter::DBClientPresenter(const QString& nameDB)
{
    this->m_nameDB=nameDB;

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

 void DBClientPresenter::createDB(const QString&  nameDB)
 {
     this->m_nameDB=nameDB;

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
       params="id INTEGER PRIMARY KEY AUTOINCREMENT,messange TEXT,idDialog INTEGER ";
       str=m_req.createTable(m_tabMessages,params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabMessages;
             qDebug() << m_query->lastError().text();
      }
      else
        qDebug()<<"The table "<<m_tabMessages<<" is creating";

  }


   bool DBClientPresenter::insertUser(User us)
   {
       QString params="login";
       QString values="'%1'";

       QString str_insert=m_req.insertData(m_tabUsers,params,values);
       QString str=str_insert.arg(us.getLogin());

       if (!m_query->exec(str))
         {
           qDebug() << "Unable to make insert operation";
           return false;
       }
       else
          {
           qDebug() << "To make insert operation";
           return true;
}
   }


   bool DBClientPresenter::insertDialog(const int& id1,const int& id2 )
   {
       QString params="idSender, idReceiver";
       QString values="%1, %2";

       QString str_insert=m_req.insertData(m_tabUsers,params,values);
       QString str=str_insert.arg(id1).arg(id2);

       if (!m_query->exec(str))
         {
           qDebug() << "Unable to make insert operation";
           return false;
       }
       else
          {
           qDebug() << "To make insert operation";
           return true;
       }
   }

   int DBClientPresenter::searchIdDialog(const int& id1,const int& id2)
   {
       int id=-1;

       QString params="id";
       QString values="idSender="+QString::number(id1)+"AND idReceiver="+QString::number(id2);
       QString str=m_req.searchData(m_tabUsers,params,values);

         m_query->exec(str);
         if(m_query->next())
            {

                id= m_query->value(0).toInt();
                qDebug()<<"The data search";

            }
            else
             qDebug()<<"The data dosn't search";

         return id;
   }

   bool DBClientPresenter::insertMessage(const QString& mess,const int& idDialog)
   {
       QString params="messange, idDialogs";
       QString values="'%1',%2";

       QString str_insert=m_req.insertData(m_tabUsers,params,values);
       QString str=str_insert.arg(mess).arg(idDialog);

       if (!m_query->exec(str))
         {
           qDebug() << "Unable to make insert operation";
           return false;
       }
       else
          {
           qDebug() << "To make insert operation";
           return true;
}
   }


