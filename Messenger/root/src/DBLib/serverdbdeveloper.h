#pragma once

class ServerDBDeveloper: public DBDeveloper
{
public:
    ServerDBDeveloper();

     virtual DB* Create();
     virtual DB* Create(QString);
};
