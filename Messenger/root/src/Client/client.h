#pragma once

#include<QObject>

//#include"guilib.h"
#include"ClientConnect.h"


class Client: public QObject
{

  Q_OBJECT
private:
    //GuiLib m_gui;
    ClientConnection m_client;
    QVector<int> m_vecClients;

public:
    Client(QObject* obj=0);

   virtual ~Client();


    void startWork();



public slots:
    void slotAuthorization(QString,QString);
    void slotConnection(QString,QString);
    void slotRegistration(QString,QString);
    void slotHello();


    void slotGetListsClients(QVector<int>);
   void slotSendMessage();
   void slotSendInfo();
};

