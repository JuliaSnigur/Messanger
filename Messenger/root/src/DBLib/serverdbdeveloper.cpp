#include"stdafx.h"
#include "serverdbdeveloper.h"

ServerDBDeveloper::ServerDBDeveloper()//:DBDeveloper()
{}

DB* ServerDBDeveloper::Create()
{
    qDebug()<<"I'm server data base";
    DB* db=new ServerDB();
    return db;
}

DB* ServerDBDeveloper::Create(QString name)
{
    DB* db=new ServerDB(name);
    return db;
}
