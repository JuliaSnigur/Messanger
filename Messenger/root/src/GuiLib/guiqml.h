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

    Q_PROPERTY(QString m_error READ getError NOTIFY errorChange)


    Q_PROPERTY(QQmlListProperty<Element> data READ data NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data")


public:
    GuiQML(QObject* parent=0);
    virtual ~GuiQML();

    QString getLogin() const;
    QString getPassword() const;

    QString getPort() const;
    QString getIP() const;

    QString getError() const;


    QQmlListProperty<Element> data();



 Q_INVOKABLE void connection(const QString& ip, const QString& port);
 Q_INVOKABLE void registration(const QString& login, const QString& pass);
 Q_INVOKABLE void authirization(const QString& login, const QString& pass);
 Q_INVOKABLE void getListFriends();
 Q_INVOKABLE void choiceFriend(const int& id);


public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);

    void setPort(const QString&);
    void setIP(const QString&);


    void slotRespond( QString res);



signals:
    void loginChange (const QString& login);
    void passwordChange (const QString& pass);
    void portChange (const QString& port);
    void ipChange (const QString& ip);
    void errorChange (const QString& error);
    void dataChanged();


     void signalConnection(const QString& ip, int port);
     void signalAuthorisation( QString login, QString pass);
     void signalRegistration( QString login, QString pass);
     void  signalGetListFriends();
     void signalChoiceFriend(const int& id);


     void signalSuccessConect();
     void signalSuccessRegistr();
     void signalSuccessAuthor();
     void signalError();


private:


    static void appendData(QQmlListProperty<Element> *list, Element *value);
    static int countData(QQmlListProperty<Element> *list);
    static Element *atData(QQmlListProperty<Element> *list, int index);
    static void clearData(QQmlListProperty<Element> *list);

    QList<Element*> m_data;

    QString m_login;
    QString m_password;

    QString m_port;
    QString m_ip;

    QString m_error;


};

}
