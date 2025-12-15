// SPDX-License-Identifier: GPL-3.0-only
/* main.cpp - Primary source file for UltradiumTimer work-break scheduling app
 *
 * Copyright (C) 2025 feeRnt; <81442162+feeRnt@users.noreply.github.com>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

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

