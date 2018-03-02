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



public:
    GuiLib(QObject* parent=0);

    QString getLogin() const;
    QString getPassword() const;

    QString getPort() const;
    QString getIP() const;


 Q_INVOKABLE void connection();



public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);

    void setPort(const QString&);
    void setIP(const QString&);

signals:
    void loginChange (const QString&);
     void passwordChange (const QString&);

     void portChange (const QString&);
      void ipChange (const QString&);

      void signalConnection( QString, QString );
      void signalAuthorisation( QString , QString );
      void signalRegistration( QString , QString );


};
