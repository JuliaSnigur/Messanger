#pragma once

#include "stdafx.h"

struct User
{

    QString login;
    QString password;
    QString IP;
    int id;


    User():login(""),password(""),IP(""),id(0) {}

    User(QString ip, QString log,QString pas)
    {
        login=log;
        password=pas;
        IP=ip;
    }
};
/*
QDataStream& operator<<(QDataStream& obj,const User& us)
{
    obj<<us.IP<<us.login<<us.password;
    return obj;
}

QDebug& operator<<(QDebug& obj,const User& us)
{
    obj<<us.IP<<us.login<<us.password;
    return obj;
}
*/
