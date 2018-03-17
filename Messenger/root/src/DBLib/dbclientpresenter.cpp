#include "stdafx.h"

#include"request.h"
#include"user.h"
#include"dbpresenter.h"
#include "dbclientpresenter.h"

DB::DBClientPresenter::DBClientPresenter()
{
    this->m_nameDB = "Client_db.db";

    m_tabDialogs = "dialogs";
    m_tabMessages = "messages";
    m_tabFiles = "files";
}

DB::DBClientPresenter::~DBClientPresenter(){}

DB::DBClientPresenter::DBClientPresenter(const QString& nameDB):DBClientPresenter()
{
    this->m_nameDB = nameDB;

      try{
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
     this->m_nameDB = nameDB;

     m_tabDialogs = "dialogs";
     m_tabMessages = "messages";
     m_tabFiles = "files";

       try{
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
      //table dialogs

      QString params = "id INTEGER PRIMARY KEY AUTOINCREMENT,idFriend INTEGER ";
      QString str = Request::createTable(m_tabDialogs, params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabDialogs;
             qDebug() << m_query->lastError().text();
      }
      qDebug() << "The table " << m_tabDialogs << " is creating";

      //table messages

       params = "id INTEGER PRIMARY KEY AUTOINCREMENT,idDialog INTEGER, state BOOLEAN, time TEXT, message TEXT, idFile INTEGER ";
       str=Request::createTable(m_tabMessages,params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabMessages;
             qDebug() << m_query->lastError().text();
      }
      else
        qDebug() << "The table " << m_tabMessages << " is creating";

      // table files
       params = "id INTEGER PRIMARY KEY AUTOINCREMENT,filename TEXT,file BLOB ";
       str = Request::createTable(m_tabFiles, params);

      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tabFiles;
             qDebug() << m_query->lastError().text();
      }
      else
        qDebug()<< "The table " << m_tabFiles << " is creating";

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

       QString params = "state, time, message, idFile";
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
       int idDialog = -1;

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

   bool DB::DBClientPresenter::insertMessage(const int& idDialog,const bool& state, const QString& mess, const QString& time, const int& idFile)
   {
       QString params=" idDialog, state, message, time, idFile ";
       QString values=" %1, %2, '%3', '%4', %5 ";

       QString str_insert=Request::insertData(m_tabMessages,params,values);
       QString str=str_insert.arg(idDialog)
                             .arg(state)
                             .arg(mess)
                             .arg(time)
                             . arg(idFile);


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

   bool DB::DBClientPresenter::insertFile( QString filename,  QByteArray file)
   {
       QString params="filename, file";
       QString values=":Name, :File";

       m_query->prepare( "INSERT INTO "+m_tabFiles+" ( "+params+") VALUES ("+values+")");
       m_query->bindValue(":Name",filename);
       m_query->bindValue(":File", file);

       if (!m_query->exec())
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

   QVariantList DB::DBClientPresenter::searchFile(const int& id)
   {
       QVariantList list;

       QString params='*';
       QString values="id="+QString::number(id);
       QString str=Request::searchData(m_tabFiles,params,values);

       qDebug()<<str;
         m_query->exec(str);
         if(m_query->next())
            {
             list.append(m_query->value(1).toString());
             list.append(m_query->value(2).toByteArray());
             qDebug()<<"The data search";
            }
            else
             qDebug()<<"The data dosn't search";

         return list;
   }


