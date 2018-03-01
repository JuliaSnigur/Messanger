#pragma once

#include "stdafx.h"

class GuiLib: public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)

    Q_PROPERTY(QString m_port WRITE setPort READ getPort NOTIFY portChange)
    Q_PROPERTY(QString m_ip WRITE setIP READ getIP NOTIFY ipChange)


private:
    QString m_login;
    QString m_password;

    QString m_port;
    QString m_ip;
   // MyClient cl;



public:
    GuiLib(QObject* parent=0);

    QString getLogin() const;
    QString getPassword() const;

    QString getPort() const;
    QString getIP() const;


public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);

    void setPort(const QString&);
    void setIP(const QString&);

signals:
    void loginChange (QString);
     void passwordChange (QString);

     void portChange (QString);
      void ipChange (QString);



};
