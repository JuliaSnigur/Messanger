#pragma once

class DBServerPresenter: public DBPresenter
{
public:
    DBServerPresenter();

    virtual ~DBServerPresenter();


    bool insertUser(User us);

    User* searchUser(const QString& login);
    int searchID(const QString& login);
    QString searchLogin(const int&);

protected:
    virtual void createTables();

private:
   QString m_tabUsers;
};

