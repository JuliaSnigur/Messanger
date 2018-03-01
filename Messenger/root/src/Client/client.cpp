#include"stdafx.h"
#include "client.h"

Client::Client():m_db(),m_gui(),m_client()
{
  //  m_client.createConnection("127.0.0.1",27015);
}

Client::~Client(){}


void Client::startWork()
{
    try
    {
        m_db.createConnection();
        m_db.createTables();
    }
    catch(std::exception& ex)
    {
        qDebug()<<ex.what();
    }

    User us("fdfd","fdfdfd");

    //m_client.sendToServer(us.getLogin(),us.getPassword());

    m_db.insertUser(us);

    try
    {

        User* user =m_db.searchUser(us.getLogin());
    }
    catch(std::exception& ex)
    {
        qDebug()<<ex.what();
    }
}


