#include"stdafx.h"

#include <QCoreApplication>
#include <QGuiApplication>
#include<QtQml/QQmlApplicationEngine>




int main(int argc, char *argv[])
{
    QCoreApplication  app(argc, argv);

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
