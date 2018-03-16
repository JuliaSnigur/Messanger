#include "stdafx.h"

#include "element.h"


Element::Element(QObject *parent)
    : QObject(parent)
    , m_color()
    , m_text("")
    , m_id(0)
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
    return m_text;
}

void Element::setText(QString text)
{
    if (m_text == text) {
        return;
    }

    m_text = text;

    emit textChanged(m_text);
}

int Element::id() const
{
    return m_id;
}
