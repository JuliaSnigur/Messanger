#include"stdafx.h"
#include "userstable.h"

UsersTable::UsersTable(){}

UsersTable::UsersTable(QString str):TableDataBase(str){}

 UsersTable::~UsersTable(){}

 QString UsersTable::createTable()
 {
     return  "CREATE TABLE "+m_name+" (id INTEGER PRIMARY KEY AUTOINCREMENT,login TEXT UNIQUE,password TEXT,status INTEGER);";
 }


  QString UsersTable::insertData()
  {
     return "INSERT INTO "+m_name+" (login,password,status) VALUES ('%1', '%2',%3);";
  }

   QString UsersTable::searchData(QString str)
   {
       return "SELECT id, login, password, status FROM "+m_name+" WHERE "+str+";";
   }

   QString UsersTable::updateData(QString str1,QString str2)
   {
        return "UPDATE  "+m_name+" SET "+str1+" WHERE "+str2+";";
   }
