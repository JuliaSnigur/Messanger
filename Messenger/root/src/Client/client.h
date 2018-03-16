#pragma once

#include<QObject>

#include"guiqml.h"
#include"ClientConnect.h"


class Client: public QObject
{

  Q_OBJECT
private:

    ClientConnection m_client;
    Gui::GuiQML m_gui;

public:
    Client(QObject* obj=0);

   virtual ~Client();

    void startWork();
    Gui::GuiQML& getGui();
};

