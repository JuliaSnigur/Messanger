#pragma once

class TableDataBase
{
protected:
    QString m_name;

public:
    TableDataBase();
    TableDataBase(QString);

    virtual ~TableDataBase();


    QString getName();
    void setName(QString);


    virtual QString createTable()=0;
    virtual QString insertData()=0;
    virtual QString searchData(QString)=0;
    virtual QString updateData(QString,QString)=0;

};

