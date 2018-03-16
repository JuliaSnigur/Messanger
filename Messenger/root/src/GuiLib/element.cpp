#include "stdafx.h"

#include "element.h"

Element::Element(QObject *parent)
    : QObject(parent)
    , m_color()
    , m_login("")
    , m_time("")
    , m_idFile(0)
{
}

QString Element::color() const
{
    return m_color;
}

void Element::setColor(QString color)
{
    if (m_color == color) {
        return;
    }

    m_color = color;

    emit colorChanged(m_color);
}

QString Element::login() const
{
    return m_login;
}

void Element::setLogin(QString text)
{
    if (m_login == text) {
        return;
    }

    m_login = text;

    emit loginChanged(m_login);
}

  int Element::idFile() const
  {
      return m_idFile;
  }

QString Element::time() const
{
    return m_time;
}
QString Element::message() const
{
    return m_message;
}

void Element::setMessage(QString mess)
{
    if (m_message == mess) {
        return;
    }

    m_message = mess;

    emit messageChanged(m_message);
}

void Element::setIdFile(int idFile)
{
    if (m_idFile == idFile) {
        return;
    }

    m_idFile = idFile;

    emit idFileChanged(m_idFile);
}

void Element::setTime(QString time)
{
    if (m_time == time) {
        return;
    }

    m_time = time;

    emit timeChanged(m_time);
}
