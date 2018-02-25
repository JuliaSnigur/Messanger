<<<<<<< HEAD
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "stdafx.h"

=======
#include "stdafx.h"

#include"clientlib.h"

>>>>>>> master
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

<<<<<<< HEAD
  //  qmlRegisterType<SignIn> ("SignIn", 1, 0, "SignIn");

  //  QQmlApplicationEngine engine;
   // engine.load (QUrl (QStringLiteral ("../GuiLib/main.qml") ) ) ;
=======
    qmlRegisterType<SignIn> ("SignIn", 1, 0, "SignIn");

    QQmlApplicationEngine engine;
    engine.load (QUrl (QStringLiteral ("../../src/GuiLib/Authorization.qml") ) ) ;
>>>>>>> master

    return app.exec();
}
