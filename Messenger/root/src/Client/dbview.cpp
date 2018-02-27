#include"stdafx.h"
#include "dbview.h"

DBView::DBView():m_dbPres()
{

}

 DBView::~DBView()
{

}

  void DBView::createConnection()
  {
      m_dbPres.createConnection();
  }

  void DBView::createTables()
  {
      m_dbPres.createTables();
  }

   void DBView::insertUsers(User& us)
   {
       m_dbPres.insertUser(us);
   }
