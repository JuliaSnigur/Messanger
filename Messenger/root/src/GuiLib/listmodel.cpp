#include"stdafx.h"

#include "listmodel.h"
#include"element.h"
#include"parsedata.h"

Gui::MyListModel::MyListModel(QObject *parent):
    QObject(parent)
{
    Element *element = new Element(this);
    element->setProperty("color", "lightgreen");
    element->setProperty("text", "eldest");

    m_data << element;

}



QQmlListProperty<Element> Gui::MyListModel::data()
{
    return QQmlListProperty< Element >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_data),
                                       &MyListModel::appendData,
                                       &MyListModel::countData,
                                       &MyListModel::atData,
                                       &MyListModel::clearData);
}

void Gui::MyListModel::add( Element* elem)
{

     m_data << elem;

    emit dataChanged();
}

void Gui::MyListModel::appendData(QQmlListProperty<Element> *list, Element *value)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    data->append(value);
}

int Gui::MyListModel::countData(QQmlListProperty<Element> *list)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    return data->size();
}

Element *Gui::MyListModel::atData(QQmlListProperty<Element> *list, int index)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    return data->at(index);
}

void Gui::MyListModel::clearData(QQmlListProperty<Element> *list)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}


void Gui::MyListModel::slotGetFriend()
{
   // QHash<int,QString> hash=StringHandlNamespace::separateHash(list);

    Element* element = new Element(this);
    element->setProperty("text", "Julia");

    m_data<<element;

  //  QHash<int,QString>::const_iterator iter = list.begin();
/*
    while(iter != list.end())
    {
        Element* element = new Element(this);
        element->setProperty("text", iter.value());

        m_listModel.add(element);
    }
    */
}




