#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TimerManager.h"
#include "QuotesManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerManager timerManager;
    QuotesManager quotesManager(":/quotes.csv");

    engine.rootContext()->setContextProperty("timerManager", &timerManager);
    engine.rootContext()->setContextProperty("quotesManager", &quotesManager);
    /* Loads the context (resources, headers or other stuff) under which the engine will run*/
    // qInfo() << "hello? in main.cpp";
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    /* Loads the main engine */
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

