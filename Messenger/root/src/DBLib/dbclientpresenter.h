#pragma once

#include "stdafx.h"

class DBClientPresenter: public DBPresenter
{
private:
    QString m_tabDialogs,m_tabMessages;
public:
    DBClientPresenter();

  virtual  ~DBClientPresenter();


     virtual void createTables();

     virtual void insertUser(User&);
     void insertDialog();

};

