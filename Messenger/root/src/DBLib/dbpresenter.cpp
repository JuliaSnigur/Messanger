#include <QDebug>
#include <QSqlError>

#include "request.h"
#include "user.h"
#include "dbpresenter.h"

DB::DBPresenter::DBPresenter()
{}

DB::DBPresenter::~DBPresenter()
{
    m_db.close();
}

void DB::DBPresenter::createConnection()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName( m_nameDB);
    if (!m_db.open())
    {
          qDebug()<<"Can't open database: "<< m_db.lastError();
          throw std::exception("Can't open database");
    }
    qDebug() << "Database's opening";
    m_query = std::shared_ptr<QSqlQuery>(new QSqlQuery(m_db));
}

 void DB::DBPresenter::deleteDB()
 {
     m_db.removeDatabase(m_nameDB);
 }
