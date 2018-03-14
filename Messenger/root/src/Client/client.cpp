#include"stdafx.h"


#include"guiqml.h"

#include"client.h"


Client::Client(QObject* obj)
    :QObject(obj)
     ,m_gui()
     ,m_client()
{

    connect(&m_client,&ClientConnection::signalGetListsClients,this,&Client::slotGetListsClients);
    connect(&m_client,&ClientConnection::signalSendMessage,this,&Client::slotSendMessage);
    connect(&m_client,&ClientConnection::signalSendInfo,this,&Client::slotSendInfo);


    connect(&m_gui,&GuiQML::signalConnection,&m_client,&ClientConnection::slotConnection);
    connect(&m_gui,&GuiQML::signalRegistration,&m_client,&ClientConnection::slotRegistration);
    connect(&m_gui,&GuiQML::signalAuthorisation,&m_client,&ClientConnection::slotAuthorization);

    connect(&m_client,&ClientConnection::signalError,&m_gui,&GuiQML::slotError);
    connect(&m_client,&ClientConnection::signalSuccessful,&m_gui,&GuiQML::slotRespond);

}

Client::~Client()
{
}


void Client::startWork()
{
    qDebug()<<"______________________________";
  m_client.slotConnection("127.0.0.1",27015);

   // QString filename="txt.txt";
   // m_client.sendFile(filename);

}


void Client::slotAuthorization(QString login,QString password)
{
    qDebug()<<"Authorization";
}

void Client::slotConnection( QString ip,QString port)
{
    qDebug()<<"Connection";
   // m_client.start("127.0.0.1",27015);
     m_client.slotConnection(ip,port.toInt());
}

void Client::slotRegistration( QString login, QString password)
{
    qDebug()<<"Registration";
}

 void Client::slotHello()
{
    qDebug()<<"Hello";
}



 void Client::slotGetListsClients(QVector<int> vec)
 {
      m_vecClients=vec;
      m_client.setIdFriend(0);
      emit m_client.signalSendMessage();
 }


  void Client::slotSendMessage()
  {
          int idFriend=0;

          qDebug()<<"My friend-> "<<idFriend;

          std::string mess;

         std::cout<<"Message: ";
         std::getline(std::cin,mess);

         m_client.setIdFriend(idFriend);
         m_client.sendMessage(QString::fromStdString(mess));


  }

  void Client::slotSendInfo()
  {
      std::string login,password;
      std::cout<<"Login: ";
      std::cin>>login;
      std::cout<<"Password: ";
      std::cin>>password;

      m_client.slotRegistration(QString::fromStdString(login),QString::fromStdString(password));



}

  GuiQML& Client::getGui()
  {
      return this->m_gui;
  }
