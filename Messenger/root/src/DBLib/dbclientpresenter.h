#pragma once

#include<QQueue>
#include<QVariantList>

class DBClientPresenter: public DBPresenter
{
private:
    QString m_tabDialogs,m_tabMessages,m_tabFiles;

protected:

     virtual void createTables();

public:
    DBClientPresenter();
    DBClientPresenter(const QString&);

  virtual  ~DBClientPresenter();




     virtual bool insertUser(User);
     bool insertDialog(int id1, int id2 );

     bool insertFile( QString filename,QByteArray file);
     QVariantList searchFile(const int& id);


     int searchIdDialog(const int& id1,const int& id2);
     bool insertMessage(const QString& mess,const int& idDialog);

     QQueue<QString> showDialog(const int& idDialog);

      void createDB(const QString& );

};

