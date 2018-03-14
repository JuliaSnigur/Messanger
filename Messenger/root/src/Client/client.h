#pragma once

#include<QObject>

#include"guiqml.h"
#include"ClientConnect.h"


class Client: public QObject
{

  Q_OBJECT
private:

    ClientConnection m_client;
    QVector<int> m_vecClients;
    GuiQML m_gui;

public:
    Client(QObject* obj=0);

   virtual ~Client();


    void startWork();

    GuiQML& getGui();

public slots:
    void slotAuthorization(QString,QString);
    void slotConnection(QString,QString);
    void slotRegistration(QString,QString);
    void slotHello();


    void slotGetListsClients(QVector<int>);
   void slotSendMessage();
   void slotSendInfo();
};

