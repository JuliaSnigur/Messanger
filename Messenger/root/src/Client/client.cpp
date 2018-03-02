#include"stdafx.h"
#include "client.h"

#include"parsedata.h"

Client::Client():m_db(),m_gui(),m_client()
{
    QObject::connect(&m_gui,SIGNAL(signalConnection(QString,QString)),this,SLOT(slotConnection(QString,QString)));

}

Client::~Client(){}


void Client::startWork()
{
   m_client.createConnection("127.0.0.1",27015);
  m_client.sendToServer(ParseData::concatenation1(Message,"Hello"));
   m_client.sendToServer(ParseData::concatenation2(Authorization,"user","123"));

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
