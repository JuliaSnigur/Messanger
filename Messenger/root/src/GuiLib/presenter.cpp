#include"stdafx.h"

#include "presenter.h"

Presenter::Presenter(QObject* parent):QObject(parent){}


QString Presenter::getLogin() const
{
    return this->m_login;
}


QString Presenter::getPassword() const
{
    return this->m_password;
}


 QString Presenter::getIP() const
 {
     return this->m_ip;
 }

void Presenter::setLogin(const QString& str)
{
    if (m_login == str)
            return;

    m_login = str;
    emit loginChange(m_login);

}

void Presenter::setPassword(const QString& str)
{
    if (m_password == str)
            return;

    m_password = str;
    emit loginChange(m_password);
}

void Presenter::setIP(const QString& str)
{
    if (m_ip == str)
            return;

    m_ip = str;
    emit ipChange(m_ip);

}


/*
void Presenter::sendRequestToServer()
{
    User us(m_ip,m_login,m_password);
    cl.sendToServer(us);
    qDebug() << "login: "<<m_login<<"\tpassword: "<<m_password;
}
*/
