#include"stdafx.h"
#include "signin.h"



SignIn::SignIn(QObject* parent):QObject(parent),cl("185.181.16.6",80){}

QString SignIn::getLogin() const
{
    return this->m_login;
}


QString SignIn::getPassword() const
{
    return this->m_password;
}


 QString SignIn::getIP() const
 {
     return this->m_ip;
 }

void SignIn::setLogin(const QString& str)
{
    if (m_login == str)
            return;

    m_login = str;
    emit loginChange(m_login);

}

void SignIn::setPassword(const QString& str)
{
    if (m_password == str)
            return;

    m_password = str;
    emit loginChange(m_password);
}

void SignIn::setIP(const QString& str)
{
    if (m_ip == str)
            return;

    m_ip = str;
    emit ipChange(m_ip);

}


void SignIn::sendRequestToServer()
{
    User us(m_ip,m_login,m_password);
    cl.sendToServer(us);
    qDebug() << "login: "<<m_login<<"\tpassword: "<<m_password;
}
