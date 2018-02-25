<<<<<<< HEAD
#ifndef SIGNIN_H
#define SIGNIN_H

#include"stdafx.h"

class SignIn: public QObject
{
private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)
=======
#pragma once

class SignIn: public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)
     Q_PROPERTY(QString m_ip WRITE setIP READ getIP NOTIFY ipChange)

>>>>>>> master

private:
    QString m_login;
    QString m_password;
<<<<<<< HEAD


public:
    SignIn();

    QString getLogin() const;
    QString getPassword() const;

    void setLogin(const QString);
   void setPassword(const QString);

   Q_INVOKABLE void sendInfoOnServer(QString,QString);


signals:
    void loginChange (QString);
    void passwordChange(QString);

};

#endif // SIGNIN_H
=======
    QString m_ip;
    MyClient cl;



public:
    SignIn(QObject* parent=0);

    QString getLogin() const;
    QString getPassword() const;
    QString getIP() const;

public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);
    void setIP(const QString&);

Q_INVOKABLE
    void sendRequestToServer();

signals:
    void loginChange (QString);
     void passwordChange (QString);
     void ipChange(QString);



};


>>>>>>> master
