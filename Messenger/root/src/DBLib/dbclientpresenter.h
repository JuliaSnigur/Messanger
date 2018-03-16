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
    DBClientPresenter(const QString& nameDB);

  virtual  ~DBClientPresenter();


     virtual bool insertUser(User);
     bool insertDialog(const int& id );

     bool insertFile( QString filename,QByteArray file);
     QVariantList searchFile(const int& id);


     int searchID(const QString& login);
     int searchIdDialog(const int& id);
     bool insertMessage(const int& idDialog,const QString& recipient, const QString& mess, const QString& time, const int& idFile=0);

     QQueue<QString> showDialog(const int& idDialog);

      void createDB(const QString& );

};

