#include"stdafx.h"

#include"secureclientlib.h"

#include"client.h"


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

    /*Client cl;

    cl.startWork();
*/

    SecureClient client;

    client.createConnection("127.0.0.1",27015);

    return app.exec();
}
