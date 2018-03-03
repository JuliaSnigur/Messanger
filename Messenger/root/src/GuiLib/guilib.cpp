#include"stdafx.h"
#include "guilib.h"



GuiLib::GuiLib(QObject* parent):QObject(parent){}

QString GuiLib::getLogin() const
{
    return this->m_login;
}


QString GuiLib::getPassword() const
{
    return this->m_password;
}


void GuiLib::setLogin(const QString& str)
{
    if (m_login == str)
            return;

    m_login = str;
    emit loginChange(m_login);

}

void GuiLib::setPassword(const QString& str)
{
    if (m_password == str)
            return;

    m_password = str;
    emit loginChange(m_password);
}


QString GuiLib::getPort() const {return m_port;}
QString GuiLib::getIP() const{return m_ip;}


void GuiLib::setPort(const QString& str)
{
    if (m_port == str)
            return;

    m_port = str;
    emit portChange(m_port);
}
void GuiLib::setIP(const QString& str)
{
    if (m_ip == str)
            return;

    m_ip = str;
    emit ipChange(m_ip);
}

/////////////////////////////////////////////

void GuiLib::connection()
{
   // emit signalConnection(m_ip,m_port);
   emit signalHello();
}


