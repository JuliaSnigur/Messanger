#pragma once

#include <QObject>

class GuiQML: public QObject
{
    Q_OBJECT
private:
    Q_PROPERTY(QString m_login WRITE setLogin READ getLogin NOTIFY loginChange)
    Q_PROPERTY(QString m_password WRITE setPassword READ getPassword NOTIFY passwordChange)

    Q_PROPERTY(QString m_port WRITE setPort READ getPort NOTIFY portChange)
    Q_PROPERTY(QString m_ip WRITE setIP READ getIP NOTIFY ipChange)
    Q_PROPERTY(QString m_error WRITE setError READ getError NOTIFY errorChange)
    Q_PROPERTY(bool m_flag WRITE setFlag READ getFlag NOTIFY flagChange)



private:
    QString m_login;
    QString m_password;

    QString m_port;
    QString m_ip;

    QString m_error;
    bool m_flag;

public:
    GuiQML(QObject* parent=0);
    virtual ~GuiQML();

    QString getLogin() const;
    QString getPassword() const;

    QString getPort() const;
    QString getIP() const;

    QString getError() const;
    bool getFlag()const;


 Q_INVOKABLE void connection(const QString& ip, const QString& port);
 Q_INVOKABLE void registration(const QString& login, const QString& pass);
 Q_INVOKABLE void authirization(const QString& login, const QString& pass);


public slots:
    void setLogin(const QString&);
    void setPassword(const QString&);

    void setPort(const QString&);
    void setIP(const QString&);

    void setError(const QString&);

    void setFlag(const bool& error);

    void slotRespond(int respond);
    void slotError(const QString& error);



signals:
    void loginChange (const QString&);
     void passwordChange (const QString&);

     void portChange (const QString&);
      void ipChange (const QString&);
      void errorChange (const QString&);
      void flagChange(const bool&);

      void signalConnection(const QString&, int );
      void signalAuthorisation( QString , QString );
      void signalRegistration( QString , QString );

};
