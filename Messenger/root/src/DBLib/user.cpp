#include"stdafx.h"
#include "user.h"

User::User()
    : m_login("")
    , m_id(0)
    , m_password("")
    , m_status(false)
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

User::User(const QString& log, const QString& pas, const bool &status)
    : m_id(0)
    , m_login(log)
    , m_password(pas)
    , m_status(status)
{}

User::User(const int& id ,const QString& login, const bool& status)
    : m_id(id)
    , m_login(login)
    , m_status(status)
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

void User::setStatus(const bool& status)
{
    m_status = status;
}

QString User::getLogin() const
{
    return m_login;
}

QString User::getPassword() const
{
    return m_password;
}

int User::getID() const
{
    return m_id;
}

 bool  User::getStatus() const
 {
     return m_status;
 }
