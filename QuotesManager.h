// SPDX-License-Identifier: GPL-3.0-only
/* QuotesManager.h - Handle the display of quotes during the work-phase in the program
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


#pragma once

#include <QObject>
#include <QStringList>

class QuotesManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString randomQuote READ randomQuote NOTIFY quoteChanged)
    //get Q-string by reading from function randomQuote. Afterwards
    //notify with quotesChanged's emitted signal

public: //accessed by all parts of the program. Qt, QML, cpp, etc.
    QuotesManager(const QString &filePath, QObject *parent = nullptr);
    // Class constructor; run when the class is initialized

    QString randomQuote();

signals: // an emitted "signal" when something happens within the program
         // qt specialty
    void quoteChanged();

private: // Only accessible by members of this class (QuotesManager).
    QStringList m_quotes;
};

