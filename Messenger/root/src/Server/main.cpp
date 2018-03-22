#include "stdafx.h"
#include "SslServer.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Server::SslServer server;
    server.start(27015);

  //  QString str = "1 user 1 2  user2 2 ";
   // QVector<User*> vec = Data::separateVecUser(str);



    return app.exec();
}
