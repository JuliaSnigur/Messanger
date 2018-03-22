#pragma once

class User
{
private:
    QString m_login;
    QString m_password;
    int m_id;
    bool m_status;

public:

    User();
    virtual ~User();

    User(const User& obj);
    User& operator=(const User& obj);

    User(const QString& login ,const QString& password, const bool& status);
    User(const int& id ,const QString& login, const bool& status);
    User(const QString& login);

    void setLogin(const QString& login);
    void setPassword(const QString& password);
    void setID(const int& id);
    void setStatus(const bool& status);

    QString getLogin() const;
    QString getPassword() const;
    int getID() const;
    bool getStatus() const;

};

