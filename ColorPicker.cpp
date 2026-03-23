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


#include "ColorPicker.h"
#include <QColor>
#include <QtQuickDialogs2/QtQuickDialogs2>
#include <QColorDialog>



ColorPicker::ColorPicker(QWidget *parent)
    : QColorDialog(parent), m_pickedBgColor("white"), m_pickedFgColor("white")
{
}

//void ColorPicker::setCurrentColor(Qt::white)
//{
    /*if (Qt::white == "") {
        m_pickedBgColor = Qt::white;
    }*/
    //m_pickedBgColor = ColorPicker::getColor(Qt::white, this, "Pick a background color");
//    m_pickedBgColor = QColorDialog::getColor()
//}
