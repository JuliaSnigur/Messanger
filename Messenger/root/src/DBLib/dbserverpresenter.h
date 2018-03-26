#pragma once

#include <QQueue>
#include <memory>

#include "user.h"

namespace DB {
    class DBServerPresenter: public DBPresenter
    {
    public:
        DBServerPresenter();
        DBServerPresenter(const QString& nameDB);
        virtual ~DBServerPresenter();
        bool insertUser(const Data::User &us);
        std::shared_ptr<Data::User> searchUser(const QString& login);
        int searchID(const QString& login);
        QString searchLogin(const int& id);
        bool searchStatus(const int& id);
        QVector<std::shared_ptr<Data::User>> getListOfUser();
        bool updateStatus(const int& id, const bool& status);
        bool updateStatusAllClients(const bool& status);
        virtual void createTables();

    private:
       QString m_tabUsers;
    };
}
