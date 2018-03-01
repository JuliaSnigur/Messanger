#pragma once

class DBServerPresenter: public DBPresenter
{
private:

public:
    DBServerPresenter();

    virtual ~DBServerPresenter();

    virtual void createTables();
    virtual void insertUser(User);

    User* searchUser(const QString& login);
    User* searchUser(const int);



};

