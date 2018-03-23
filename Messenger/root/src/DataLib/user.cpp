#include"stdafx.h"

#include "user.h"

Data::User::User()
    : m_login("")
    , m_id(0)
    , m_password("")
    , m_status(false)
{}

Data::User::~User(){}

Data::User& Data::User::operator=(const User& obj)
{
    m_login = obj.m_login;
    m_password = obj.m_password;
    return *this;
}

Data::User::User(const User& obj)
{
    m_login = obj.m_login;
    m_password = obj.m_password;
}

Data::User::User(const QString& log, const QString& pas, const bool &status)
    : m_id(0)
    , m_login(log)
    , m_password(pas)
    , m_status(status)
{}

Data::User::User(const int& id ,const QString& login, const bool& status)
    : m_id(id)
    , m_login(login)
    , m_status(status)
{}

Data::User::User(const QString& login)
    : User()
{
    m_login = login;
}

void Data::User::setLogin(const QString& login)
{
    m_login = login;
}

void Data::User::setPassword(const QString& pass)
{
    m_password = pass;
}

void Data::User::setID(const int& id)
{
    m_id = id;
}

void Data::User::setStatus(const bool& status)
{
    m_status = status;
}

QString Data::User::getLogin() const
{
    return m_login;
}

QString Data::User::getPassword() const
{
    return m_password;
}

int Data::User::getID() const
{
    return m_id;
}

 bool  Data::User::getStatus() const
 {
     return m_status;
 }
