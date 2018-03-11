#include "stdafx.h"


//#include"ServerSocket.h"


#include "ServerConnection.h"



// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//  ServerSocket server(27015);

    ServerConnection server;
    server.start(27015);

    return app.exec();
}
