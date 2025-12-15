// SPDX-License-Identifier: GPL-3.0-only
/* TimerManager.cpp - Handle the timer functions for the work-break scheduling
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

#include "TimerManager.h"
#include <QUrl>
//#include <QDir>
#include <QDebug>

TimerManager::TimerManager(QObject *parent)
    : QObject(parent), m_remainingTime(0), m_onBreak(true), onPause(true), m_counter(0), m_ultradianModeOn(false),
    m_workPeriod_min(25), m_shortBreakPeriod_min(5), m_longBreakPeriod_min(35)          // if you don't init ultradian, then it can't calcualte total remaining time
    //call the initializer function with the QObject as *parent, and then set the values of
    //of some of the variables of this class. (of a file, in essence)
{
    connect(&m_timer, &QTimer::timeout, this, &TimerManager::updateTime);
    //sfxOutput = new ; sfxPlayer = new //use this for pointer objects,
    //sfxPlayer.setAudioOutput(sfxOutput); //use this for regular objects
    //sfxOutput.setVolume(1);
    sfxPlayer = new QMediaPlayer(this);
    sfxOutput = new QAudioOutput(this);
    sfxPlayer->setAudioOutput(sfxOutput);
    sfxOutput->setVolume(1);
}

/*
 int m_counter = 0;
bool onPause = true;
*/ // Defined in header, and initialized in constructor above

void TimerManager::start(float workDuration, float breakDuration, bool q_ultradianModeRequested, bool breakNess, int counterUser)
{
    m_workDuration = workDuration * 60;
    m_breakDuration = breakDuration * 60;
    qInfo() << "Current breakDuration " << breakDuration;
    qInfo() << "Current workDuration " << workDuration;
    qInfo() << "Current m_shortBreakPeriod_min " << m_shortBreakPeriod_min;
    qInfo() << "Current m_workPeriod_min " << m_workPeriod_min;
    m_onBreak = breakNess;
    emit breakChanged();
    m_ultradianModeRequested = q_ultradianModeRequested;
    //m_remainingTime = m_workDuration;
    //qInfo() << "Current m_onBreak = " << m_onBreak;
    m_counter = counterUser;
    qInfo() << "Current m_counter in start() = " << m_counter;
    emit counterUpdated(); //Without this emit, personalized work cycles don't work because
                           //Q_PROPERTY counter is never updated
    m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
    m_timer.start(1000); //rate of decrease
//    elapsed->start(); //will restart in case it's already started as well
}

void TimerManager::stop()
{
    m_timer.stop();
//    elapsed->restart();
    //m_remainingTime = 0;
    //m_onBreak = true;
    emit timeUpdated();
    //emit breakChanged();
}

void TimerManager::reset()
{
    m_timer.stop();
//    elapsed->restart();
    m_remainingTime = 0;
    m_workDuration = 0;
    m_breakDuration = 0;
    m_counter = 0;
    m_onBreak = true;
    m_ultradianModeOn = false;
    emit counterUpdated();
    emit timeUpdated();
    emit breakChanged();
    emit ultradianModeChanged();
}

/*void TimerManager::memberVarSetter(float &m_var, float var_value)
{
    m_var = var_value;
}*/ //Does not work as QML does not know about references, except QObject

void TimerManager::m_shortBreakPeriod_minSetter(float m_shortBreakPeriod_minSet)
{
    m_shortBreakPeriod_min = m_shortBreakPeriod_minSet;
}

void TimerManager::m_longBreakPeriod_minSetter(float m_longBreakPeriod_minSet)
{
    m_longBreakPeriod_min = m_longBreakPeriod_minSet;
}

void TimerManager::m_workPeriod_minSetter(float m_workPeriod_minSet)
{
    m_workPeriod_min = m_workPeriod_minSet;
}


void TimerManager::updateTime()
{
    m_remainingTime--;
    emit timeUpdated();
    if (m_ultradianModeRequested) { //special case where a user asks to start from the Long break, instead of n-th work cycle
        m_remainingTime = 0;
       //  m_counter = 3 - 1; // Should be added in the switch / comboBox part
    }

    if (m_remainingTime <= 0) {
        qInfo() << "time ran out. current m_counter = " << m_counter;
        if (!m_onBreak) {
            m_counter = m_counter + 1;
            emit counterUpdated(); //this is needed, otherwise it won't work
        }
        if (m_counter == 3 /*or m_ultradianModeRequested*/) { // 1 - based. Use 6, and assign to - 1 without !onBreak check
            qInfo() << "3 work periods in a row";
            m_onBreak = !m_onBreak;
            if (!m_ultradianModeRequested) { // I don't to add duplicate code for the same routine...
                sfxPlayer->setSource(QUrl(longBreakSFX));
                sfxPlayer->play();
            }
            //m_remainingTime = m_onBreak ? 30*60 : 25*60;
            //m_onBreak = true;
            m_ultradianModeOn = true;
            emit ultradianModeChanged();
            m_remainingTime = m_longBreakPeriod_min*60;
            m_counter = 0;
            emit counterUpdated();
            emit breakChanged();
            emit sessionComplete();
            //m_ultradianMode = false;
            //emit ultradianModeChanged();
            m_ultradianModeRequested = false;
            //emit ultradianModeRequestChanged();
//            elapsed->restart();
        }
        else {
        m_onBreak = !m_onBreak;
        sfxPlayer->setSource(QUrl((m_onBreak ? shortBreakSFX : workPeriodSFX)));
        sfxPlayer->play();
        //qInfo() << "will play the sound at " << shortBreakSFX;
        //m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
        m_remainingTime = m_onBreak ? m_shortBreakPeriod_min*60 : m_workPeriod_min*60;
        m_ultradianModeOn= false;
        emit ultradianModeChanged();
        emit breakChanged();
        emit sessionComplete();
        }
    }
}

