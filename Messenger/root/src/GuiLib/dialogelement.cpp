#include "dialogelement.h"

Gui::DialogElement::DialogElement(QObject* parent)
    : QObject(parent)
    , m_message("")
    , m_stateMess("")
    , m_flag()
    , m_time("")
{}

Gui::DialogElement::DialogElement()
    : m_message("")
    , m_stateMess("")
    , m_flag()
    , m_time("")
{}

QString Gui::DialogElement::time() const
{
    return m_time;
}
QString Gui::DialogElement::message() const
{
    return m_message;
}

QString Gui::DialogElement::stateMessage() const
{
    return m_stateMess;
}

bool Gui::DialogElement::flag() const
{
    return m_flag;
}



void Gui::DialogElement::setMessage(const QString& mess)
{
    if (m_message != mess)
    {
        m_message = mess;
        emit messageChanged(m_message);
    }
}

void Gui::DialogElement::setTime(const QString& time)
{
    if (m_time != time)
    {
        m_time = time;
        emit timeChanged(m_time);
    }
}

void Gui::DialogElement::setStateMessage(const QString& state)
{
    if (m_stateMess != state)
    {
        m_stateMess = state;
        emit stateMessageChanged(m_stateMess);
    }
}

void Gui::DialogElement::setFlag(const bool& flag)
{
    if (m_flag != flag)
    {
        m_flag = flag;
        emit flagChanged(m_flag);
    }
}

 void Gui::DialogElement::appendData(QQmlListProperty<DialogElement> *list, DialogElement *value)
{
    QList<DialogElement*> *data = static_cast<QList<DialogElement*> *>(list->data);
    data->append(value);
}

int Gui::DialogElement::countData(QQmlListProperty<DialogElement> *list)
{
    QList<DialogElement*> *data = static_cast<QList<DialogElement*> *>(list->data);
    return data->size();
}



 Gui::DialogElement* Gui::DialogElement::atData(QQmlListProperty<DialogElement> *list, int index)
{
    QList<DialogElement*> *data = static_cast<QList<DialogElement*> *>(list->data);
    return data->at(index);
}



 void Gui::DialogElement::clearData(QQmlListProperty<DialogElement> *list)
{
    QList<DialogElement*> *data = static_cast<QList<DialogElement*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}
