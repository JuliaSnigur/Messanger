#pragma once

namespace Request {

    QString createTable(const QString& nameTable, const QString& params);
    QString insertData(const QString& nameTable, const QString& params, const QString& values);
    QString searchData(const QString& nameTable, const QString& params, const QString& values);
    QString updateData(const QString& nameTable, const QString& params, const QString values);

}

