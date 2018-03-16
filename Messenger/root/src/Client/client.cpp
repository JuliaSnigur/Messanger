#include"stdafx.h"


#include"guiqml.h"

#include"client.h"



Client::Client(QObject* obj)
    : QObject(obj)
     , m_gui()
     , m_client()
{

    connect(&m_gui, &Gui::GuiQML::signalConnection, &m_client, &ClientConnection::slotConnection);
    connect(&m_gui, &Gui::GuiQML::signalRegistration, &m_client, &ClientConnection::slotRegistration);
    connect(&m_gui, &Gui::GuiQML::signalAuthorisation, &m_client, &ClientConnection::slotAuthorization);
    connect(&m_gui, &Gui::GuiQML::signalGetListFriends, &m_client, &ClientConnection::slotGetListFriend);
    connect(&m_gui, &Gui::GuiQML::signalSendMessage, &m_client, &ClientConnection::slotSendMessage);
    connect(&m_gui, &Gui::GuiQML::signalChoiceFriend, &m_client, &ClientConnection::slotChoiceFriend);


    connect(&m_client, &ClientConnection::signalSendRespond, &m_gui, &Gui::GuiQML::slotRespond);

}

Client::~Client()
{
}



  Gui::GuiQML& Client::getGui()
  {
      return m_gui;
  }
