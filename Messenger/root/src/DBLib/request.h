#pragma once

class Request
{
public:
    Request();

    virtual~Request();

    QString createTable(QString& nameTable,QString& params);
    QString insertData(QString& nameTable,QString& params,QString& values);
    QString searchData(QString& nameTable,QString& params,QString& values);
    QString updateData(QString& nameTable, QString& params, QString values);
};

