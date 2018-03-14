#include"stdafx.h"

#include "guiqml.h"
#include"parsedata.h"




GuiQML::GuiQML(QObject* parent)
    :QObject(parent)
    ,m_error("")
    ,m_flag(false)
{}

GuiQML::~GuiQML(){}



QString GuiQML::getLogin() const
{
    return this->m_login;
}


QString GuiQML::getPassword() const
{
    return this->m_password;
}

QString GuiQML::getError() const
{
    return this->m_error;
}


void GuiQML::setLogin(const QString& str)
{
    if (m_login == str)
            return;

    m_login = str;
    emit loginChange(m_login);

}

void GuiQML::setError(const QString& str)
{
    if (m_error == str)
            return;

    m_error = str;

    emit errorChange(m_error);

}

void GuiQML::setPassword(const QString& str)
{
    if (m_password == str)
            return;

    m_password = str;
    emit loginChange(m_password);
}


QString GuiQML::getPort() const {return m_port;}
QString GuiQML::getIP() const{return m_ip;}


void GuiQML::setPort(const QString& str)
{
    if (m_port == str)
            return;

    m_port = str;
    emit portChange(m_port);
}

void GuiQML::setIP(const QString& str)
{
    if (m_ip == str)
       return;

    m_ip = str;
    emit ipChange(m_ip);
}

void GuiQML::connection(const QString& ip, const QString& port)
{
   // m_ip="127.0.0.1";
  //  m_port="27015";
    emit signalConnection(ip,port.toInt());
}

 void GuiQML::registration(const QString& login, const QString& pass)
 {
    emit signalRegistration(login,pass);
 }

 void GuiQML::authirization(const QString& login, const QString& pass)
 {
    emit signalAuthorisation(login,pass);
 }




void GuiQML::slotRespond(int respond)
{
    switch(respond)
    {
        case Connection:

        break;

    }
}

 void GuiQML::slotError(const QString& error)
 {
     m_flag=true;
    emit errorChange (error);
 }

  bool GuiQML::getFlag()const
  {
      return this->m_flag;
  }

  void GuiQML::setFlag(const bool& str)
  {
      if (m_port == str)
              return;

      m_flag = str;
      emit flagChange(m_flag);
  }
