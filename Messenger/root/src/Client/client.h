#pragma once


class Client
{

private:
    DBServerPresenter m_db;
    GuiLib m_gui;
    MyClient m_client;

public:
    Client();

   virtual ~Client();


    void startWork();


};

