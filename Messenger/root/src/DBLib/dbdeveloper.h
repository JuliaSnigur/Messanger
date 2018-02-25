#pragma once

class DBDeveloper
{
public:
    DBDeveloper();

    virtual DB* Create()=0;
    virtual DB* Create(QString)=0;

};
