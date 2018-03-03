#pragma once

class DBClientPresenter: public DBPresenter
{
private:
    QString m_tabDialogs,m_tabMessages;

protected:

     virtual void createTables();

public:
    DBClientPresenter();

  virtual  ~DBClientPresenter();




     virtual void insertUser(User);
     void insertDialog();

};

