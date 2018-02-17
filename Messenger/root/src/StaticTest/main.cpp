#include "stdafx.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyClient c("ds",2323);
    c.show();



    return a.exec();
}

