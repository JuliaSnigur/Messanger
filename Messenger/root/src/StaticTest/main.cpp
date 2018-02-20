#include "stdafx.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyClient c("185.181.16.6",2323);
    c.show();



    return a.exec();
}

