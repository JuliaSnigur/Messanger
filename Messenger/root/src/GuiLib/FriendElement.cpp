#include "stdafx.h"

#include "FriendElement.h"

Gui::FriendElement::FriendElement(QObject *parent)
    : QObject(parent)
    , m_login("")
    , m_id(0)
    , m_status(0)
{}

 Gui::FriendElement::FriendElement()
     : m_login("")
     , m_id(0)
     , m_status(0)
 {}

QString Gui::FriendElement::login() const
{
    return m_login;
}

void Gui::FriendElement::setLogin(const QString& text)
{
    if (m_login != text)
    {
        m_login = text;
        emit loginChanged(m_login);
    }

}

int Gui::FriendElement::id() const
{
    return m_id;
}

void Gui::FriendElement::setID(const int& id)
{
    if (m_id != id)
    {
        m_id = id;
        emit idChanged(m_id);
    }
}

bool Gui::FriendElement::status() const
{
    return m_status;
}

void Gui::FriendElement::setStatus(const bool& status)
{
    if (m_status != status)
    {
        m_status = status;
        emit statusChanged(m_status);
    }
}


void Gui::FriendElement::appendData(QQmlListProperty<FriendElement> *list, FriendElement *value)
{
    QList<FriendElement*> *data = static_cast<QList<FriendElement*> *>(list->data);
    data->append(value);
}

int Gui::FriendElement::countData(QQmlListProperty<FriendElement> *list)
{
    QList<FriendElement*> *data = static_cast<QList<FriendElement*> *>(list->data);
    return data->size();
}

Gui::FriendElement* Gui::FriendElement::atData(QQmlListProperty<FriendElement> *list, int index)
{
    QList<FriendElement*>* data = static_cast<QList<FriendElement*> *>(list->data);
    return data->at(index);
}

void Gui::FriendElement::clearData(QQmlListProperty<FriendElement> *list)
{
    QList<FriendElement*> *data = static_cast<QList<FriendElement*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}


