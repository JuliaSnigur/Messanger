#pragma once

#include"stdafx.h"

class Client
{

private:
    DBView m_dbView;
    GuiLib m_gui;
    MyClient m_client;

public:
    Client();

   virtual ~Client();


    void startWork();


};

