#include"stdafx.h"
#include "request.h"


QString Request::createTable(const QString& name_tb,const QString& params)
{
    return "CREATE TABLE "+name_tb+" ("+params+");";
}

QString Request::insertData(const QString& name_tb, const QString& params,const QString& values)
{
    return "INSERT INTO "+name_tb+" ("+params+") VALUES ("+values+");";
}

 QString Request::searchData(const QString& nameTable,const QString& params,const QString& values)
 {
     return "SELECT "+params+" FROM "+nameTable+" WHERE "+values;
 }

 QString Request::updateData(const QString& nameTable,const QString& params,const QString values)
 {
      return "UPDATE  "+nameTable+" SET "+params+" WHERE "+values+";";
 }
