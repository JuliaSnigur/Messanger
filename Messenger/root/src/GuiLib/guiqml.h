#pragma once


#include <QObject>
#include<QQmlListProperty>

#include"element.h"

namespace Gui {



class GuiQML: public QObject
{
    Q_OBJECT



private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)
    Q_PROPERTY(QString m_port WRITE setPort READ getPort NOTIFY portChange)
    Q_PROPERTY(QString m_ip WRITE setIP READ getIP NOTIFY ipChange)
    Q_PROPERTY(QQmlListProperty<Element> dataClients READ dataClients NOTIFY dataClientsChanged)
    Q_PROPERTY(QQmlListProperty<Element> dataDialog READ dataDialog NOTIFY dataDialogChanged)

    Q_CLASSINFO("DefaultProperty", "dataClients")
    Q_CLASSINFO("DefaultProperty", "dataDialog")

public:
    GuiQML(QObject* parent=0);
    virtual ~GuiQML();

    QString getLogin() const;
    QString getPassword() const;
    QString getPort() const;
    QString getIP() const;


    QQmlListProperty<Element> dataClients();
    QQmlListProperty<Element> dataDialog();



 Q_INVOKABLE void connection(const QString& ip, const QString& port);
 Q_INVOKABLE void registration(const QString& login, const QString& pass);
 Q_INVOKABLE void authirization(const QString& login, const QString& pass);
 Q_INVOKABLE void getListFriends();
 Q_INVOKABLE void choiceFriend(const QString& login);
 Q_INVOKABLE void sendMessage(const QString& mess);



public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);

    void setPort(const QString&);
    void setIP(const QString&);


    void slotRespond( QString res);
    void slotShowDialog(const QQueue<QString>& q);



signals:
    void loginChange (const QString& login);
    void passwordChange (const QString& pass);
    void portChange (const QString& port);
    void ipChange (const QString& ip);
    void dataClientsChanged();
    void dataDialogChanged();


     void signalConnection(const QString& ip, int port);
     void signalAuthorisation( QString login, QString pass);
     void signalRegistration( QString login, QString pass);
     void  signalGetListFriends();
     void signalChoiceFriend(const QString& login);
     void signalSendMessage(const QString&  message);


     void signalSuccessConect();
     void signalSuccessRegistr(const QString& login);
     void signalSuccessAuthor(const QString& login);
     void signalError(const QString& error);


private:


    static void appendData(QQmlListProperty<Element> *list, Element *value);
    static int countData(QQmlListProperty<Element> *list);
    static Element *atData(QQmlListProperty<Element> *list, int index);
    static void clearData(QQmlListProperty<Element> *list);

    QList<Element*> m_dataClients;
    QList<Element*> m_dataDialog;


    QString m_login;
    QString m_password;

    QString m_port;
    QString m_ip;



};

}
