#include"stdafx.h"

#include"client.h"


int main(int argc, char *argv[])
{

    srand(time(NULL));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Client cl;
    engine.rootContext()->setContextProperty("gui", &cl.getGui());
    engine.load(QUrl(QStringLiteral("../../src/GuiLib/main.qml")));

    return app.exec();
}
