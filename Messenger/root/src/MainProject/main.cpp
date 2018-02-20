#include"stdafx.h"
#include<QHostInfo>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MyClient c("185.181.16.6",80);
    c.show();
    return a.exec();
}
