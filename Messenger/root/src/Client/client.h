#pragma once

#include "stdafx.h"

class Client: public QObject
{

  Q_OBJECT
private:
    DBServerPresenter m_db;
    GuiLib m_gui;
    MyClient m_client;

public:
    Client();

   virtual ~Client();


    void startWork();


public slots:
    void slotAuthorization(QString,QString);
    void slotConnection(QString,QString);
    void slotRegistration(QString,QString);


};

