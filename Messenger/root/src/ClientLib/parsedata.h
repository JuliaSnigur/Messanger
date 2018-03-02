#pragma once

#include "stdafx.h"

 class ParseData
{
public:
    ParseData();

   virtual ~ParseData();

    static QString concatenationVec(request,std::vector<QString>&);
    static QString concatenation2(request,const QString&,const QString&);
    static QString concatenation1(request,const QString&);


    static std::queue<QString> separetionQStr(QString);
    static std::queue<QByteArray> separetionQByte(QString);
};

