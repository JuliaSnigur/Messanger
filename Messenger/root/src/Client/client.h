#pragma once

#include<QObject>

#include "guiqml.h"
#include "ClientConnect.h"

class QObject;

class MainClient: public QObject
{
  Q_OBJECT
private:
    Client::ClientConnection m_client;
    Gui::GuiQML m_gui;

public:
    MainClient(QObject* obj = 0);
    void startWork();
    Gui::GuiQML& getGui();
};

