#include"stdafx.h"


//#include"guilib.h"

#include"client.h"


Client::Client(QObject* obj)
    :QObject(obj)
    ,/*m_gui(),*/
      m_client()
{

    connect(&m_client,&ClientConnection::signalGetListsClients,this,&Client::slotGetListsClients);
    connect(&m_client,&ClientConnection::signalSendMessage,this,&Client::slotSendMessage);
    connect(&m_client,&ClientConnection::signalSendInfo,this,&Client::slotSendInfo);

}

Client::~Client()
{
}


void Client::startWork()
{
    qDebug()<<"______________________________";
   m_client.start("127.0.0.1",27015);
}


void Client::slotAuthorization(QString login,QString password)
{
    qDebug()<<"Authorization";
}

void Client::slotConnection( QString ip,QString port)
{
    qDebug()<<"Connection";
    //  m_client.createConnection("127.0.0.1",27015);
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

      m_client.registration(QString::fromStdString(login),QString::fromStdString(password));
  }
