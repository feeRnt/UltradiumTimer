// SPDX-License-Identifier: GPL-3.0-only
/* colorpicker.h - Handle background and foreground color selection for UltradiumTimer
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
#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QObject>
//#include <QQuickItem>
//#include <QDialog>
#include <QColor>
#include <QColorDialog>

class ColorPicker : public QColorDialog
{
    Q_OBJECT
    Q_PROPERTY(QColor pickedBgColor READ pickedBgColor NOTIFY updatePickedBgColor)
    Q_PROPERTY(QColor pickedFgColor READ pickedFgColor NOTIFY updatePickedFgColor)
public:
    explicit ColorPicker(QWidget *parent = nullptr);

    QColor pickedBgColor() const { return m_pickedBgColor; }
    QColor pickedFgColor() const { return m_pickedFgColor; }
signals:
    void updatePickedBgColor();
    void updatePickedFgColor();

private:
    QColor m_pickedBgColor;
    QColor m_pickedFgColor;
};

#endif // COLORPICKER_H
