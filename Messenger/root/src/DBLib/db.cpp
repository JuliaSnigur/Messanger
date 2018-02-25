#include"stdafx.h"
#include "db.h"

DB::DB(): m_query(NULL)
{
}

DB::DB(QString nameDB):m_query(NULL)
{
    m_nameBase=nameDB;
}

 bool DB::createConnection()
 {
     m_db = QSqlDatabase::addDatabase("QSQLITE");
     m_db.setDatabaseName(m_nameBase);
     if (!m_db.open())
     {
           qDebug()<<"Cannot open database: "<< m_db.lastError();
           return false;
     }
     m_query=new QSqlQuery(m_db);



     return true;


 }
