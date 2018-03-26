#include <QDebug>
#include <QQueue>

#include "request.h"
#include "user.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

DB::DBClientPresenter::DBClientPresenter()
{
    m_nameDB += "Client_db.db";
    m_tabDialogs = "dialogs";
    m_tabMessages = "messages";
}

DB::DBClientPresenter::~DBClientPresenter(){}

DB::DBClientPresenter::DBClientPresenter(const QString& nameDB):DBClientPresenter()
{
    m_nameDB =  nameDB;
      try
      {
          createConnection();
          createTables();
      }
      catch(const std::exception& ex)
      {
          qDebug() << ex.what();
      }
}

 void DB::DBClientPresenter::createDB(const QString&  nameDB)
 {
     m_nameDB =  nameDB;
     m_tabDialogs = "dialogs";
     m_tabMessages = "messages";
     try
     {
         createConnection();
         createTables();
      }
      catch(const std::exception& ex)
      {
           qDebug() << ex.what();
      }
 }


  void DB::DBClientPresenter::createTables()
  {
      QString params = "id INTEGER PRIMARY KEY AUTOINCREMENT,idFriend  INTEGER UNIQUE";
      QString str = Request::createTable(m_tabDialogs, params);
      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabDialogs;
      }
      qDebug() << "The table " << m_tabDialogs << " is creating";

      params = "id INTEGER PRIMARY KEY AUTOINCREMENT,idDialog INTEGER, state BOOLEAN, time TEXT, message TEXT";
      str=Request::createTable(m_tabMessages,params);
      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabMessages;
      }
      else
        qDebug() << "The table " << m_tabMessages << " is creating";

  }

   bool DB::DBClientPresenter::insertDialog(const int& id)
   {
       QString params = "idFriend";
       QString values = "%1";
       QString str_insert = Request::insertData(m_tabDialogs, params, values);
       QString str = str_insert.arg(id);
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


   QQueue<QString> DB::DBClientPresenter::showDialog(const int& idDialog)
   {
       QQueue<QString> dialog;
       QString params = "state, time, message";
       QString values = "idDialog=" + QString::number(idDialog);
       QString str =Request::searchData(m_tabMessages,params,values);
       m_query->exec(str);
       while(m_query->next())
       {
          str = "";
          // str = state, time, messange
          str += m_query->value(0).toString() + ' ';
          str += m_query->value(1).toString() + ' ';
          str += m_query->value(2).toString();
          dialog.push_back(str);
        }
         return dialog;
   }


   int DB::DBClientPresenter::searchIdDialog(const int& id)
   {
       int idDialog = 0;
       QString params = "id";
       QString values = "idFriend = " + QString::number(id);
       QString str = Request::searchData(m_tabDialogs, params, values);
       m_query->exec(str);
       if(m_query->next())
       {
          idDialog = m_query->value(0).toInt();
          qDebug() << "The data search";
       }
       else
          qDebug() << "The data dosn't search";
       return idDialog;
   }

   bool DB::DBClientPresenter::insertMessage(const int& idDialog,const bool& state, const QString& mess, const QString& time)
   {
       QString params=" idDialog, state, message, time";
       QString values=" %1, %2, '%3', '%4'";
       QString str_insert=Request::insertData(m_tabMessages,params,values);
       QString str=str_insert.arg(idDialog)
                             .arg(state)
                             .arg(mess)
                             .arg(time);
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





