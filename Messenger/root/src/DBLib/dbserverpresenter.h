#pragma once



class DBServerPresenter: public DBPresenter
{
private:

protected:
    virtual void createTables();

public:
    DBServerPresenter();

    virtual ~DBServerPresenter();


    virtual bool insertUser(User);

    User searchUser(const QString& login);
    User searchUser(const int);
    int searchID(const QString& login);
    QString searchLogin(const int&);



};

