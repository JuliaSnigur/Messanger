#include "stdafx.h"

#include "SslServer.h"



// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Server::SslServer server;
    server.start(27015);

    return app.exec();
}
