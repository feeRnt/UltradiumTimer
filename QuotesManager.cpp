// SPDX-License-Identifier: GPL-3.0-only
/* QuotesManager.cpp - Handle the display of quotes during the work-phase in the program
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

#include "QuotesManager.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>

QuotesManager::QuotesManager(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    QFile file(filePath);

    //qInfo() << "hello?";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        //skips first 2 copyright lines, and the empty line after
        for (int skip = 1; skip < 3; ++skip) {
                in.readLine();
        }
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty())
                m_quotes << line;
        }
        file.close();
    } else {
        qWarning() << "Could not open quotes file:" << filePath;
    }
}

QString QuotesManager::randomQuote()
{
    if (m_quotes.isEmpty())
        return "No quotes found.";

    int index = QRandomGenerator::global()->bounded(m_quotes.size());
    //qInfo() << "All quotes are: " << m_quotes;
    /*
     * qInfo() << "Printing nth line of quotesfile. n = " << index;
     * qInfo() << "It will be this: " << m_quotes.at(index);
    */
    return m_quotes.at(index);
}

