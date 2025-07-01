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

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

