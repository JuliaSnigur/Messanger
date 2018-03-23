#pragma once

#include<QQueue>

namespace DB {

    class DBServerPresenter: public DBPresenter
    {
    public:
        DBServerPresenter();
        DBServerPresenter(const QString& nameDB);

        virtual ~DBServerPresenter();

        bool insertUser(const User &us);

        User* searchUser(const QString& login);
        int searchID(const QString& login);
        QString searchLogin(const int& id);
        bool searchStatus(const int& id);
        QVector<User*> getListOfUser();
        bool updateStatus(const int& id, const bool& status);

    protected:
        virtual void createTables();

    private:
       QString m_tabUsers;
    };

}
