#pragma once

#include <QString>

namespace Request {

    QString createTable(const QString& nameTable, const QString& params);
    QString insertData(const QString& nameTable, const QString& params, const QString& values);
    QString searchData(const QString& nameTable, const QString& params, const QString& values);
    QString searchAllData(const QString& nameTable, const QString& params);
    QString updateData(const QString& nameTable, const QString& params, const QString values);
    QString updateAllData(const QString& nameTable, const QString& params);
}

