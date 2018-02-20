#include "signin.h"

SignIn::SignIn(){}

QString SignIn::getLogin() const
{
    return this->m_login;
}


QString SignIn::getPassword() const
{
    return this->m_password;
}

void SignIn::sendInfoOnServer(QString log,QString pas)
{
    m_login=log;
    m_password=pas;

}


