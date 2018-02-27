#include"stdafx.h"
#include "user.h"

User::User():m_login(""),m_id(0),m_password(""),m_status(false)
{

}

User& User::operator=(const User& obj)
{
    this->m_login=obj.m_login;
    this->m_password=obj.m_password;
    this->m_status=obj.m_status;
    return *this;
}

User::User(const User& obj)
{
    this->m_login=obj.m_login;
    this->m_password=obj.m_password;
    this->m_status=obj.m_status;
}

User::User(QString log,QString pas,bool st):m_id(0),m_login(log),m_password(pas),m_status(st){}

void User::setLogin(QString a){this->m_login=a;}
void User::setPassword(QString a){m_password=a;}
void User::setStatus(bool a){m_status=a;}
void User::setID(int a){m_id=a;}


QString User::getLogin(){return this->m_login;}
QString User::getPassword(){return this->m_password;}
bool User::getStatus(){return this->m_status;}
int User::getID(){return this->m_id;}
