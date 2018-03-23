#include"stdafx.h"

#include"guiqml.h"
#include "ClientConnect.h"
#include"client.h"

MainClient::MainClient(QObject* obj)
     : QObject(obj)
     , m_gui(this)
     , m_client(this)
{
    connect(&m_gui, &Gui::GuiQML::signalConnection, &m_client, &Client::ClientConnection::slotConnection);
    connect(&m_gui, &Gui::GuiQML::signalRegistration, &m_client, &Client::ClientConnection::slotRegistration);
    connect(&m_gui, &Gui::GuiQML::signalAuthorisation, &m_client, &Client::ClientConnection::slotAuthorization);
    connect(&m_gui, &Gui::GuiQML::signalGetListFriends, &m_client, &Client::ClientConnection::slotGetListFriend);
    connect(&m_gui, &Gui::GuiQML::signalSendMessage, &m_client, &Client::ClientConnection::slotSendMessage);
    connect(&m_gui, &Gui::GuiQML::signalChoiceFriend, &m_client, &Client::ClientConnection::slotChoiceFriend);
    connect(&m_gui, &Gui::GuiQML::signalSendFile, &m_client, &Client::ClientConnection::slotSendFile);

    connect(&m_client, &Client::ClientConnection::signalSendRespond, &m_gui, &Gui::GuiQML::slotRespond);
    connect(&m_client, &Client::ClientConnection::signalSendDialog, &m_gui, &Gui::GuiQML::slotShowDialog);
}

Gui::GuiQML& MainClient::getGui()
{
    return m_gui;
}
