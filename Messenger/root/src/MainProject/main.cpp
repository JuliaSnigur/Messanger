#include"stdafx.h"
#include<QHostInfo>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

<<<<<<< HEAD:Messenger/root/src/MainProject/main.cpp
    MyClient c("185.181.16.6",80);
=======
    MyClient c("185.181.16.6",2323);
>>>>>>> c1b816110e8540f2d8049e21465c3c382c4d088d:Messenger/root/src/StaticTest/main.cpp
    c.show();
    return a.exec();
}
