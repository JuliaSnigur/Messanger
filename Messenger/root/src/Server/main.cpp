#include "stdafx.h"


#include"ServerSocket.h"
#include"secureserverlib.h"

using namespace ServerNamespace;



// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

  // ServerSocket server(27015);

    SecureServer server;
    server.createServer(27015);

    return app.exec();
}
