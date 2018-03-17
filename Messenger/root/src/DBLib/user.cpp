#include"stdafx.h"
#include "user.h"

User::User()
    : m_login("")
    , m_id(0)
    , m_password("")
{}

User::~User(){}

User& User::operator=(const User& obj)
{
    m_login = obj.m_login;
    m_password = obj.m_password;
    return *this;
}

User::User(const User& obj)
{
    m_login = obj.m_login;
    m_password = obj.m_password;
}

User::User(const QString& log,const QString& pas)
    : m_id(0)
    , m_login(log)
    , m_password(pas)
{}

User::User(const QString& login)
    : User()
{
    m_login = login;
}

void User::setLogin(const QString& login)
{
    m_login = login;
}

void User::setPassword(const QString& pass)
{
    m_password = pass;
}

void User::setID(const int& id)
{
    m_id = id;
}


QString User::getLogin()
{
    return m_login;
}

QString User::getPassword()
{
    return m_password;
}

int User::getID()
{
    return m_id;
}
