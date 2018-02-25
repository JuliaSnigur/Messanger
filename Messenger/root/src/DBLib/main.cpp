#include <QCoreApplication>

#include"stdafx.h"



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);


    DBDeveloper* dev=new ServerDBDeveloper();
    DB* serverDB=dev->Create("D:/Qt MSVS2015/Server_bd.db");



    if(!serverDB->createConnection())
        qDebug()<<"Not connection";
    else
        qDebug()<<"There is connection";

   // serverDB->createTable();

    User us("user1","1023");

   serverDB->insertData(us);
    User* user=serverDB->userSearchID(1);


    qDebug()<<user->getID()<<" "<<user->getLogin()<<" "<<user->getPassword()<<" "<<user->getStatus();

    user=serverDB->userSearchLogin("user");
   // user=serverDB->userSearchLoginPassword("user","1023");
if(user)
    qDebug()<<user->getID()<<" "<<user->getLogin()<<" "<<user->getPassword()<<" "<<user->getStatus();

serverDB->updateStatus(1);

    return a.exec();
}
