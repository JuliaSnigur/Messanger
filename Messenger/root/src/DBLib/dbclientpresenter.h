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
     bool insertDialog(const int& id1,const int& id2 );

     int searchIdDialog(const int& id1,const int& id2);
     bool insertMessage(const QString& mess,const int& idDialog);


      void createDB(const QString& );

};

