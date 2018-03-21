#include "stdafx.h"

#include "guiqml.h"
#include "data.h"

#include "FriendElement.h"
#include "dialogelement.h"




Gui::GuiQML::GuiQML(QObject* parent)
    : QObject(parent)
{
    //qmlRegisterType<FriendElement>("Element", 1, 0, "Element");
    //qmlRegisterType<DialogElement>("Element", 1, 0, "Element");
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

     QString time=QTime::currentTime().toString();

     emit signalSendMessage(time + ' ' + mess);

     DialogElement* element = new DialogElement(this);

     element->setProperty("flag", Send);
     element->setProperty("time", time);
     element->setProperty("message", mess);
     element->setProperty("idFile", 0);

     m_dataDialog << element;
     emit dataDialogChanged();
 }

//////////////////////////////////////////////////////

void Gui::GuiQML::slotRespond( QString res)
{
     QHash<int,QString> hash;
     QHash<int,QString>::const_iterator iter;

    switch((Data::variable(res)).toInt())
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

        hash = Data::separateHash(res);

        iter = hash.begin();

         while(iter != hash.end())
         {
             FriendElement* element = new FriendElement(this);

             qDebug() << iter.key() << ' ' << iter.value();

             element->setProperty("login", iter.value());

             m_dataClients << element;
             emit dataClientsChanged();


             ++iter;
         }

        break;

    case GetFriend:
        // отображение диалога
        break;

    case Message:

        DialogElement* element = new DialogElement(this);

        // str =  time, messange

        element->setProperty("flag", Get);
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
         DialogElement* element = new DialogElement(this);

         str = q[i];

         // str = flag, time, messange, idFile
         element->setProperty("flag", (Data::variable(str)).toInt());
         element->setProperty("time", Data::variable(str));
         element->setProperty("message", str);

         m_dataDialog << element;

         emit dataDialogChanged();
     }
}


void Gui::GuiQML::sendFile(const QUrl& mess)
{

}


////////////////////////////////


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





