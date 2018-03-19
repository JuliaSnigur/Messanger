#include"stdafx.h"
#include "request.h"

Request::Request()
{

}

Request::~Request(){}

QString Request::createTable(QString& name_tb,QString& params)
{
    return "CREATE TABLE "+name_tb+" ("+params+");";
}

QString Request::insertData(QString& name_tb,QString& params,QString& values)
{
    return "INSERT INTO "+name_tb+" ("+params+") VALUES ("+values+");";
}

 QString Request::searchData(QString& nameTable,QString& params,QString& values)
 {
     return "SELECT "+params+" FROM "+nameTable+" WHERE "+values;
 }

 QString Request::updateData(QString& nameTable, QString& params, QString values)
 {
      return "UPDATE  "+nameTable+" SET "+params+" WHERE "+values+";";
 }
