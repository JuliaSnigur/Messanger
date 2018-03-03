#include"stdafx.h"

#include"request.h"
#include "user.h"
#include"ipresenter.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

#include"guilib.h"
#include"ClientSocket.h"
#include"parsedata.h"

#include"client.h"



using namespace ClientNamespace;
using namespace StringHandlNamespace;



Client::Client(QObject* obj):QObject(obj),m_db(),m_gui(),m_client(m_db),m_isStartDialog(false)
{

    //connect(&m_gui,SIGNAL(signalConnection(QString,QString)),this,SLOT(slotConnection(QString,QString)));
   // connect(&m_gui,&GuiLib::signalHello, this, &Client::slotHello);

    connect(&m_client,&ClientSocket::signalInsertUserIntoTabSession,this,&Client::slotInsertUserIntoTabSession);
    connect(&m_client,&ClientSocket::signalGetListsClients,this,&Client::slotGetListsClients);
    connect(&m_client,&ClientSocket::signalGetID,this,&Client::slotGetID);




}

Client::~Client()
{
}


void Client::startWork()
{
    qDebug()<<"______________________________";
   m_client.createConnection("127.0.0.1",27015);

   std::string login,password;
   std::cout<<"Login: ";
   std::cin>>login;
   std::cout<<"Password: ";
   std::cin>>password;

   m_us.setLogin(QString::fromStdString(login));
   m_us.setPassword(QString::fromStdString(password));

   m_client.sendToServer(QString::number(Registration)+' '+m_us.getLogin()+' '+m_us.getPassword());




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

 void Client::slotInsertUserIntoTabSession()
 {
     // id
    m_db.insertUser(m_us);
 }

 void Client::slotGetListsClients(QVector<int> vec)
 {
     m_isStartDialog=true;
      m_vecClients=vec;

     qDebug()<<"Get list";

     dialog();

 }

  void Client::slotGetID(int id)
  {
      m_us.setID(id);
  }

  void Client::dialog()
  {
      if(m_isStartDialog)
       {
          int idFriend=m_vecClients[rand()%m_vecClients.size()];
          while(m_us.getID()==idFriend)
              idFriend=m_vecClients[rand()%m_vecClients.size()];

          qDebug()<<"My friend-> "<<idFriend;
          std::string mess;

          while(true)
         {
              std::cout<<"Message: ";
              std::getline(std::cin,mess);

              // serchDialog
              // createDialog

              // insertMessage

            // req,receiver,text
            //  m_client.sendToServer(QString::number(Message)+' '+/*my id*/+' '+QString::number(idFriend)+mess);
              m_client.sendToServer(QString::number(Message)+" "+QString::number(idFriend)+" "+QString::fromStdString(mess));
         }
        }
  }
