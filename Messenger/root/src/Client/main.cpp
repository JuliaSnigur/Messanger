#include"stdafx.h"



#include"parsedata.h"



#include"request.h"
#include "user.h"
#include"ipresenter.h"
#include "dbpresenter.h"
#include "dbclientpresenter.h"

#include"guilib.h"
#include"ClientSocket.h"

#include"client.h"
using namespace ClientNamespace;

using namespace StringHandlNamespace ;


int main(int argc, char *argv[])
{
    QCoreApplication  app(argc, argv);

    srand(time(NULL));

  /*  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<GuiLib> ("GuiLib", 1, 0, "GuiLib");

    QQmlApplicationEngine engine;

    engine.load (QUrl (QStringLiteral ("../../src/GuiLib/main.qml") ) ) ;
*/
    Client cl;

    cl.startWork();


    return app.exec();
}
