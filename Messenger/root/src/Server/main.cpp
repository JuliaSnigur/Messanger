#include "stdafx.h"


#include"ServerSocket.h"

using namespace ServerNamespace;



// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

   ServerSocket server(27015);




    return app.exec();
}
