#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "stdafx.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

  //  qmlRegisterType<SignIn> ("SignIn", 1, 0, "SignIn");

  //  QQmlApplicationEngine engine;
   // engine.load (QUrl (QStringLiteral ("../GuiLib/main.qml") ) ) ;

    return app.exec();
}
