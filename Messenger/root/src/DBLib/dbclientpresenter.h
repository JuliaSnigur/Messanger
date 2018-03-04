#pragma once

class DBClientPresenter: public DBPresenter
{
private:
    QString m_tabDialogs,m_tabMessages;

protected:

     virtual void createTables();

public:
    DBClientPresenter();
    DBClientPresenter(const QString&);

  virtual  ~DBClientPresenter();




     virtual bool insertUser(User);
     void insertDialog();

      void createDB(const QString& );

};

