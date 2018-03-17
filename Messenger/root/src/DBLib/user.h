#pragma once

class User
{
private:
    QString m_login;
    QString m_password;
    int m_id;

public:

    User();
    virtual ~User();

    User(const User& obj);
    User& operator=(const User& obj);

    User(const QString& login ,const QString& password);
    User(const QString& login);

    void setLogin(const QString& login);
    void setPassword(const QString& password);
    void setID(const int&);

    QString getLogin();
    QString getPassword();
    int getID();

};

