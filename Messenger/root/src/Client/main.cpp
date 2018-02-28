#include"stdafx.h"

#include <QCoreApplication>
//#include <QGuiApplication>
//#include<QtQml/QQmlApplicationEngine>

#include "clientlib.h"
//#include"presenter.h"


int main(int argc, char *argv[])
{
    QCoreApplication  app(argc, argv);

    MyClient client();


  /*  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Presenter> ("Presenter", 1, 0, "Presenter");

    QQmlApplicationEngine engine;

    engine.load (QUrl (QStringLiteral ("../../src/GuiLib/Authorization.qml") ) ) ;
*/
    return app.exec();
}
