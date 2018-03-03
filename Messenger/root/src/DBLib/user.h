#pragma once

#include"stdafx.h"

class User
{
private:
    QString m_login;
    QString m_password;
    bool m_status;
    int m_id;

public:

    User();
    User(const User&);
    User(QString,QString,bool st=false);

    User& operator=(const User& obj);

    void setLogin(QString);
    void setPassword(QString);
    void setStatus(bool);
    void setID(int);

    QString getLogin();
    QString getPassword();
    bool getStatus();
    int getID();

};

