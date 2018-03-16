#include"stdafx.h"

#include "guiqml.h"
#include"parsedata.h"

#include"element.h"




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


///////////////////////////////////////////////////////

void Gui::GuiQML::connection(const QString& ip, const QString& port)
{

    emit signalConnection(ip,port.toInt());
}


 void Gui::GuiQML::registration(const QString& login, const QString& pass)
 {
    m_login=login;
    emit loginChange(login);
    emit signalRegistration(login,pass);
 }

 void Gui::GuiQML::authirization(const QString& login, const QString& pass)
 {
    m_login=login;
    emit loginChange(login);
    emit signalAuthorisation(login,pass);
 }


 void Gui::GuiQML::getListFriends()
 {
     emit  signalGetListFriends();
 }


 void Gui::GuiQML::choiceFriend(const QString& login)
 {
     m_dataDialog.clear();
     emit dataDialogChanged();

     emit signalChoiceFriend(login);
 }

 void Gui::GuiQML::sendMessage(const QString& mess)
 {
     emit signalSendMessage(mess);
 }



//////////////////////////////////////////////////////


void Gui::GuiQML::slotRespond( QString res)
{
     QHash<int,QString> hash;
     QHash<int,QString>::const_iterator iter;

    switch((StringHandlNamespace::variable(res)).toInt())
    {
    case Error:

        emit signalError(res);

      break;

    case Connection:
        emit signalSuccessConect();
        break;

    case Registration:
        emit signalSuccessRegistr(m_login);
        break;

    case Authorization:
        emit signalSuccessAuthor(m_login);
        break;

    case GetListOfFriends:

        m_dataClients.clear();
        emit dataClientsChanged();

        qDebug() << res;

        hash = StringHandlNamespace::separateHash(res);

        iter = hash.begin();

         while(iter != hash.end())
         {
             Element* element = new Element(this);

             qDebug() << iter.key() << ' ' << iter.value();

             element->setProperty("login", iter.value());

             m_dataClients << element;
             emit dataClientsChanged();


             ++iter;
         }

        break;

    case GetFriend:
        break;

    case Message:


        Element* element = new Element(this);

        // str = loginRecipeint, time, messange, idFile
        element->setProperty("login", StringHandlNamespace::variable(res));
        element->setProperty("time", StringHandlNamespace::variable(res));
        element->setProperty("messange", StringHandlNamespace::variable(res));
        element->setProperty("idFile", StringHandlNamespace::variable(res));

        m_dataDialog << element;
        emit dataDialogChanged();

        break;
    }

}


void Gui::GuiQML::slotShowDialog(const QQueue<QString>& q)
{
    QString str;

    for(int i = 0; i<q.size(); i++)
     {
         Element* element = new Element(this);

         str = q[i];

         // str = loginRecipeint, time, messange, idFile
         element->setProperty("login", StringHandlNamespace::variable(str));
         element->setProperty("time", StringHandlNamespace::variable(str));
         element->setProperty("messange", StringHandlNamespace::variable(str));
         element->setProperty("idFile", StringHandlNamespace::variable(str));

         m_dataClients << element;

         emit dataClientsChanged();
     }
}





////////////////////////////////


QQmlListProperty<Element> Gui::GuiQML::dataClients()
{
    return QQmlListProperty< Element >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_dataClients),
                                       &GuiQML::appendData,
                                       &GuiQML::countData,
                                       &GuiQML::atData,
                                       &GuiQML::clearData);
}

QQmlListProperty<Element> Gui::GuiQML::dataDialog()
{
    return QQmlListProperty< Element >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_dataDialog),
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




