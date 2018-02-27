#pragma once

#include"stdafx.h"

class DBServerPresenter: public DBPresenter
{
private:

public:
    DBServerPresenter();

    virtual ~DBServerPresenter();

    virtual void createTables();
    virtual void insertUser(User&);
};

