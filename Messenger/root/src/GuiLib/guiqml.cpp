#include "stdafx.h"

#include "guiqml.h"
#include "DataLib/data.h"

#include "FriendElement.h"
#include "dialogelement.h"

Gui::GuiQML::GuiQML(QObject* parent)
    : QObject(parent)
{
    qmlRegisterType<FriendElement>("Element", 1, 0, "Element");
    qmlRegisterType<DialogElement>("Element", 1, 0, "Element");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
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

QString Gui::GuiQML::getPort() const
{
    return m_port;
}

QString Gui::GuiQML::getIP() const
{
    return m_ip;
}

void Gui::GuiQML::setLogin(const QString& str)
{
    if (m_login != str)
    {
        m_login = str;
        emit loginChange(m_login);
    }

}

void Gui::GuiQML::setPassword(const QString& str)
{
    if (m_password != str)
    {
        m_password = str;
        emit loginChange(m_password);
    }


}

void Gui::GuiQML::setPort(const QString& str)
{
    if (m_port != str)
    {
        m_port = str;
        emit portChange(m_port);
    }
}

void Gui::GuiQML::setIP(const QString& str)
{
    if (m_ip != str)
    {
        m_ip = str;
        emit ipChange(m_ip);
    }
}

///////////////////////////////////////////////////////

void Gui::GuiQML::connection(const QString& ip, const QString& port)
{
    if(ip == "" || port == "")
    {
        emit signalError("Wrong data");
        return;
    }

    emit signalConnection(ip,port.toInt());
}


 void Gui::GuiQML::registration(const QString& login, const QString& pass)
 {
    if(login == "" || pass == "")
    {
        emit signalError("Wrong data");
        return;
    }
    m_login=login;
    emit loginChange(login);
    emit signalRegistration(login,pass);
 }

 void Gui::GuiQML::authirization(const QString& login, const QString& pass)
 {
    if(login == "" || pass == "")
    {
        emit signalError("Wrong data");
        return;
    }
    m_login=login;
    emit loginChange(login);
    emit signalAuthorisation(login,pass);
 }

 void Gui::GuiQML::getListFriends()
 {
     emit  signalGetListFriends();
 }

 void Gui::GuiQML::choiceFriend(const int& id)
 {
     m_dataDialog.clear();
     emit dataDialogChanged();
     emit signalChoiceFriend(id);
 }

 void Gui::GuiQML::sendMessage(const QString& mess)
 {

     QString time=QTime::currentTime().toString();

     emit signalSendMessage(time + ' ' + mess);

     DialogElement* element = new DialogElement();
     element->setProperty("flag", Data::Send);
     element->setProperty("time", time);
     element->setProperty("message", mess);
     element->setProperty("idFile", 0);
     m_dataDialog << element;
     emit dataDialogChanged();
 }

//////////////////////////////////////////////////////

void Gui::GuiQML::slotRespond( QString res)
{
    QVector<Data::User*> vec;
    switch((Data::variable(res)).toInt())
    {
    case Data::Error:
        emit signalError(res);
      break;

    case  Data::Connection:
        emit signalSuccessConect();
        break;

    case  Data::Registration:
        emit signalSuccessRegistr(m_login);
        break;

    case  Data::Authorization:
        emit signalSuccessAuthor(m_login);
        break;

    case  Data::GetListOfFriends:
        m_dataClients.clear();
        emit dataClientsChanged();
        qDebug() << res;
        vec =Data::separateVecUser(res);
        for(int i = 0; i<vec.size(); i++)
        {
            FriendElement* element = new FriendElement();
            qDebug() << vec[i]->getID() << ' ' << vec[i]->getLogin() << ' ' << vec[i]->getStatus();
            element->setProperty("id", vec[i]->getID());
            element->setProperty("login", vec[i]->getLogin());
            element->setProperty("status", vec[i]->getStatus());
            m_dataClients << element;
            emit dataClientsChanged();
        }
        break;

    case  Data::Message:
        DialogElement* element = new DialogElement();
        // str =  time, messange
        element->setProperty("flag",  Data::Get);
        element->setProperty("time", Data::variable(res));
        element->setProperty("message", res);
        m_dataDialog << element;
        emit dataDialogChanged();
        break;
    }

}


void Gui::GuiQML::slotShowDialog(const QQueue<QString>& q)
{
    m_dataDialog.clear();
    emit dataDialogChanged();
    QString str;
    for(int i = 0; i<q.size(); i++)
     {
         DialogElement* element = new DialogElement();
         str = q[i];
         // str = flag, time, messange, idFile
         element->setProperty("flag", (Data::variable(str)).toInt());
         element->setProperty("time", Data::variable(str));
         element->setProperty("message", str);
         m_dataDialog << element;
         emit dataDialogChanged();
     }
}

void Gui::GuiQML::sendFile(const QString& filePath)
{
    QString str;
    for(int i = 8; i < filePath.size();i++)
    {
        str += filePath[i];
    }
    qDebug() << str;
    emit signalSendFile(str);
}


QQmlListProperty<Gui::FriendElement> Gui::GuiQML::dataClients()
{
    return QQmlListProperty< Gui::FriendElement >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_dataClients),
                                       &FriendElement::appendData,
                                       &FriendElement::countData,
                                       &FriendElement::atData,
                                       &FriendElement::clearData);
}

QQmlListProperty<Gui::DialogElement> Gui::GuiQML::dataDialog()
{
    return QQmlListProperty< Gui::DialogElement >(static_cast<QObject *>(this),
                                       static_cast<void *>(&m_dataDialog),
                                       &DialogElement::appendData,
                                       &DialogElement::countData,
                                       &DialogElement::atData,
                                       &DialogElement::clearData);
}





