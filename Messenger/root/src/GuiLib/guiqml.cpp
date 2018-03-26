#include <QObject>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include <QDateTime>
#include <QDebug>

#include "guiqml.h"
#include "data.h"
#include "DataLib/user.h"

#include "FriendElement.h"
#include "dialogelement.h"

Gui::GuiQML::GuiQML(QObject* parent)
    : QObject(parent)
    , reg(" ")
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
    qDebug() << ip << ' ' << port;
    if(ip == "" || port == "")
    {
        emit signalError("Wrong data");
        return;
    }
    if(ip.contains(reg) || port.contains(reg))
    {
        emit signalError("Wrong data: the data consists space");
        return;
    }
    emit signalConnection(ip,port.toInt());
}


 void Gui::GuiQML::registration(const QString& login, const QString& pass)
 {
     qDebug() << login << ' ' << pass;
    if(login == "" || pass == "")
    {
        emit signalError("Wrong data");
        return;
    }
    if( login.contains(reg) || pass.contains(reg))
    {
        emit signalError("Wrong data: the data consists space");
        return;
    }
    m_login=login;
    emit loginChange(login);
    emit signalRegistration(login,pass);
 }

 void Gui::GuiQML::authirization(const QString& login, const QString& pass)
 {
    qDebug() << login << ' ' << pass;
    if(login == "" || pass == "")
    {
        emit signalError("Wrong data");
        return;
    }
    if( login.contains(reg) || pass.contains(reg))
    {
        emit signalError("Wrong data: the data consists space");
        return;
    }
    m_login = login;
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
     QString time=QDateTime::currentDateTime().toString();
     emit signalSendMessage(time + ' ' + mess);
     DialogElement* element = new DialogElement(this);
     element->setProperty("flag", Data::Send);
     element->setProperty("time", time);
     element->setProperty("message", mess);
     m_dataDialog << element;
     emit dataDialogChanged();
 }
//////////////////////////////////////////////////////
void Gui::GuiQML::slotRespond( QString res)
{
    QStringList list;
    QString time = "";
    switch(variable(res).toInt())
    {
    case Data::Info:
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
        list = res.split(' ', QString::SkipEmptyParts);
        for(int i = 0; i < list.size() - 2; i += 3)
        {
            FriendElement* element = new FriendElement(this);
            qDebug() << list[i] << ' ' << list[i + 1] << ' ' << list[i + 2];
            element->setProperty("id", list[i].toInt());
            element->setProperty("login", list[i+1]);
            element->setProperty("status", list[i+2].toInt());
            m_dataClients << element;
            emit dataClientsChanged();
        }
        break;

    case Data::File:
        emit signalError(res);
        emit signalSuccessSendFile();
        break;

    case  Data::Message:
        DialogElement* element = new DialogElement(this);
        // str =  time, messange
        element->setProperty("flag",  Data::Get);
        for(int i = 0; i < 5 ; i++)
        {
            time += variable(res) + ' ';
        }
        element->setProperty("time", time);
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

    QString str = "";
    QString time = "";
    for(int i = 0; i<q.size(); i++)
     {
         time = "";
         DialogElement* element = new DialogElement(this);
         str = q[i];
         // str = flag, time, messange
         element->setProperty("flag", variable(str).toInt());
         for(int i = 0; i < 5 ; i++)
         {
             time += variable(str) + ' ';
         }
         element->setProperty("time", time);
         element->setProperty("message", str);
         m_dataDialog << element;
         emit dataDialogChanged();
     }
}


void Gui::GuiQML::sendFile(const QString& filePath)
{
    QString path = filePath.section(":///",1);
    qDebug() << "Path: " << path;
    emit signalSendFile(path);
    emit signalError("Sending file on server...");
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

const QString Gui::GuiQML::variable(QString& str)
{
    QString res = str.section(' ', 0,0);
    QString st = str;
    str = st.section(' ',1);
    return res;
}




