#include "stdafx.h"
#include "serverdb.h"

#include"tabledatabase.h"

ServerDB::ServerDB()
{

   m_tableUsers=new UsersTable("customers");


}

 ServerDB::~ServerDB()
 {
     delete m_tableUsers;
 }

 ServerDB::ServerDB(QString nameDB):ServerDB()
 {
     m_nameBase=nameDB;

 }


 void ServerDB::insertData( User& us)
 {
      QString str_insert=m_tableUsers->insertData();
      QString str = str_insert.arg(us.getLogin()).arg(us.getPassword()).arg(us.getStatus());

      if (!m_query->exec(str))
          qDebug() << "Unable to make insert operation";
      else
          qDebug() << "To make insert operation";
 }

  bool ServerDB::createTable()
  {
      QString str=m_tableUsers->createTable();
      if(!m_query->exec(str))
      {
             qDebug() << "DataBase: error of create " << m_tableUsers->getName();
             qDebug() << m_query->lastError().text();
             return false;
       }

      return true;
  }

 User* ServerDB::userSearchID(int id)
 {
    User* us=NULL;

    char str[256]="";
    sprintf(str,"id=%d",id);

      m_query->exec(m_tableUsers->searchData(str));
      if(m_query->next())
         {
             us=new User();
             us->setID( m_query->value(0).toInt());
             us->setLogin( m_query->value(1).toString());
             us->setPassword(m_query->value(2).toString());
             us->setStatus( m_query->value(3).toBool());
             qDebug()<<"The data search";
              return us;

         }
         else
         {
            qDebug()<<"The data dosn't search";
          }
     // бросаем исключение
 }

 User* ServerDB::userSearchLoginPassword(string log,string pass)
 {
     User* us=NULL;

     string str="login='"+log+"' AND password='"+pass+"'";

     QString st=m_tableUsers->searchData(str.c_str());
       m_query->exec(st);

       if(m_query->next())
          {
              us=new User();
              us->setLogin( m_query->value(0).toString());
              us->setPassword(m_query->value(1).toString());
              us->setStatus( m_query->value(2).toBool());
              qDebug()<<"The data search";
               return us;

          }
          else
          {
             qDebug()<<"The data dosn't search";
           }
      // бросаем исключение
 }

   User* ServerDB::userSearchLogin(string log)
   {
       User* us=NULL;

       char str[256]="";
       sprintf(str,"login='%s'",log.c_str());

         m_query->exec(m_tableUsers->searchData(str));
         if(m_query->next())
            {
                us=new User();
                us->setID( m_query->value(0).toInt());
                us->setLogin( m_query->value(1).toString());
                us->setPassword(m_query->value(2).toString());
                us->setStatus( m_query->value(3).toBool());
                qDebug()<<"The data search";
                 return us;

            }
            else
            {
               qDebug()<<"The data dosn't search";
             }
        // бросаем исключение
   }

   bool ServerDB::updateStatus(int id)
    {

       User* us=userSearchID(id);
       if(us==NULL)
       {
           qDebug()<<"user=NUll";
           return false;
       }

       QString strSet="status = :int";
       QString strWhere="id = :id";

       m_query->prepare(m_tableUsers->updateData(strSet,strWhere));

       m_query->bindValue(":int", !us->getStatus());
       m_query->bindValue(":id", id);

       if(!m_query->exec())
           qDebug()<<"The data dosn't update";
       else
           qDebug()<<"The data update";

       return true;


    }
