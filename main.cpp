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
#include "ColorPicker.h"
#include "EyeTimer.h"

/* #include <QFontDatabase> */
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    /* QFontDatabase::addApplicationEmojiFontFamily(":/Fonts/seguiemj.ttf"); */
    // Seems the problem with emojis is in just selecting the unicode values.. */
    TimerManager timerManager;
    QuotesManager quotesManager(":/quotes.csv");
    EyeTimer eyeTimer;

    engine.rootContext()->setContextProperty("timerManager", &timerManager);
    engine.rootContext()->setContextProperty("quotesManager", &quotesManager);
    /* Loads the context (resources, headers or other stuff) under which the engine will run*/
    /*                        Loads the C++ &quotesManager as "quotesManger" in QML         */
    /* qInfo() << "Creating colorPicker instance of ColorPicker";
    ColorPicker colorPicker;
    qInfo() << "Loading &colorPicker as colorPicker in QML";
    engine.rootContext()->setContextProperty("colorPicker", &colorPicker); */
    // QWidget: Cannot create a QWidget without QApplication
    engine.rootContext()->setContextProperty("eyeTimer", &eyeTimer);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    /* Loads the main QML engine; it needs a QGuiApplication (QApplication) first to function. */


    if (engine.rootObjects().isEmpty())
        return -1;

    qInfo() << "Closing application normally.";
    return app.exec();
}

