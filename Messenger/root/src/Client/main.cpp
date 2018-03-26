#include <QObject>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include"client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    MainClient cl;
    engine.rootContext()->setContextProperty("gui", &cl.getGui());
    engine.load(QUrl(QStringLiteral("../../src/GuiLib/main.qml")));
    return app.exec();
}
