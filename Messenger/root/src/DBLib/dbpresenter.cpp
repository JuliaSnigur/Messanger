#include "stdafx.h"
#include "dbpresenter.h"

DBPresenter::DBPresenter()
{

}

DBPresenter::~DBPresenter(){}


void DBPresenter::createConnection()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_nameDB);
    if (!m_db.open())
    {
          qDebug()<<"Cannot open database: "<< m_db.lastError();
          throw std::exception("Cannot open database");
    }
    qDebug()<<"Database's opening";

    m_query=new QSqlQuery(m_db);
}
