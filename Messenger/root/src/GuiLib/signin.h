#ifndef SIGNIN_H
#define SIGNIN_H

#include"stdafx.h"

class SignIn: public QObject
{
private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)

private:
    QString m_login;
    QString m_password;


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
