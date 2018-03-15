#include"stdafx.h"

#include "guiqml.h"
#include"parsedata.h"

#include"element.h"

#include<QDebug>


Gui::GuiQML::GuiQML(QObject* parent)
    : QObject(parent)
{
    qDebug()<<"Hello";

    qmlRegisterType<Element>("Element", 1, 0, "Element");

}

Gui::GuiQML::~GuiQML(){}



QString Gui::GuiQML::getLogin() const
{
    return m_login;
}


QString Gui::GuiQML::getPassword() const
{
    return m_password;
}


void Gui::GuiQML::setLogin(const QString& str)
{
    if (m_login == str)
            return;

    m_login = str;
    emit loginChange(m_login);

}

void Gui::GuiQML::setPassword(const QString& str)
{
    if (m_password == str)
            return;

    m_password = str;
    emit loginChange(m_password);
}


QString Gui::GuiQML::getPort() const {return m_port;}
QString Gui::GuiQML::getIP() const{return m_ip;}


void Gui::GuiQML::setPort(const QString& str)
{
    if (m_port == str)
            return;

    m_port = str;
    emit portChange(m_port);
}

void Gui::GuiQML::setIP(const QString& str)
{
    if (m_ip == str)
       return;

    m_ip = str;
    emit ipChange(m_ip);
}

 QString Gui::GuiQML::getError() const
 {
     return m_error;
 }

///////////////////////////////////////////////////////

void Gui::GuiQML::connection(const QString& ip, const QString& port)
{
   // m_ip="127.0.0.1";
  //  m_port="27015";
    emit signalConnection(ip,port.toInt());
}


 void Gui::GuiQML::registration(const QString& login, const QString& pass)
 {
    emit signalRegistration(login,pass);
 }

 void Gui::GuiQML::authirization(const QString& login, const QString& pass)
 {
    emit signalAuthorisation(login,pass);
 }


 void Gui::GuiQML::getListFriends()
 {
     emit  signalGetListFriends();
 }


 void Gui::GuiQML::choiceFriend(const int& id)
 {
     emit signalChoiceFriend(id);
 }



//////////////////////////////////////////////////////


void Gui::GuiQML::slotRespond( QString res)
{

    switch((StringHandlNamespace::variable(res)).toInt())
    {
    case Error:

        m_error=res;
        emit signalError();

      break;

    case Connection:
        emit signalSuccessConect();
        break;

    case Registration:
        emit signalSuccessRegistr();
        break;

    case Authorization:
        emit signalSuccessAuthor();
        break;

    case GetListOfFriends:

            qDebug()<<res;
         QHash<int,QString> hash=StringHandlNamespace::separateHash(res);

         QHash<int,QString>::const_iterator iter = hash.begin();



         while(iter != hash.end())
         {
             Element* element = new Element(this);
             element->setProperty("text", iter.value());
             m_data << element;

             emit dataChanged();

             ++iter;
         }



        break;



    }

}

////////////////////////////////


QQmlListProperty<Element> Gui::GuiQML::data()
{
    return QQmlListProperty< Element >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_data),
                                       &GuiQML::appendData,
                                       &GuiQML::countData,
                                       &GuiQML::atData,
                                       &GuiQML::clearData);
}



void Gui::GuiQML::appendData(QQmlListProperty<Element> *list, Element *value)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    data->append(value);
}

int Gui::GuiQML::countData(QQmlListProperty<Element> *list)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    return data->size();
}

Element *Gui::GuiQML::atData(QQmlListProperty<Element> *list, int index)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    return data->at(index);
}

void Gui::GuiQML::clearData(QQmlListProperty<Element> *list)
{
    QList<Element*> *data = static_cast<QList<Element*> *>(list->data);
    qDeleteAll(data->begin(), data->end());
    data->clear();
}




