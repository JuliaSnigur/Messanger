#pragma once

#include <memory>
#include <QSqlDatabase>
#include <QSqlQuery>

#include<DBLib/request.h>

namespace DB {
    class DBPresenter
    {
    public:
        DBPresenter();
        virtual ~DBPresenter();
        virtual void createConnection();
        void deleteDB();

    protected:
        QString m_nameDB;
        QSqlDatabase m_db;
        std::shared_ptr<QSqlQuery> m_query;

        virtual void createTables()=0;
    };
}
