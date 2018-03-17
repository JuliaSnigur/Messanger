#include "stdafx.h"

#include"request.h"

#include"user.h"
#include "dbpresenter.h"




DB::DBPresenter::DBPresenter()
{
}

DB::DBPresenter::~DBPresenter()
{
}


void DB::DBPresenter::createConnection()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_nameDB);

    if (!m_db.open())
    {
          qDebug()<<"Cannot open database: "<< m_db.lastError();
          throw std::exception("Cannot open database");
    }
    qDebug() << "Database's opening";

    m_query = std::shared_ptr<QSqlQuery>(new QSqlQuery(m_db));
}

