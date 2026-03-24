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
// #include <QDir>
#include <QDebug>

#include "SFXPlayer.h"
// #include "EyeTimer.h"

TimerManager::TimerManager(QObject *parent)
    : QObject(parent), m_remainingTime(0), m_onBreak(true), m_counter(0), m_ultradianModeOn(false),
    m_workPeriod_min(25), m_shortBreakPeriod_min(5), m_longBreakPeriod_min(35) /*,onPause(true)*/
    // if you don't init ultradian, then it can't calcualte total remaining time

    // Period_min are the default values, Duration are the called upon values.
    // TODO: fix this insane naming scheme with normalize *_default variables as in EyeTimer.h/cpp

    //call the initializer function with the QObject as *parent, and then set the values of
    //of some of the variables of this class. (of a file, in essence)
    //set QObject as QObject
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

void TimerManager::start(float qml_workDuration, float qml_breakDuration, bool qml_ultradianModeRequested, bool breakness, int counterUser)
{
    m_workDuration = qml_workDuration * 60;
    m_breakDuration = qml_breakDuration * 60;
    qInfo() << "Current breakDuration " << qml_breakDuration;
    qInfo() << "Current workDuration " << qml_workDuration;
    qInfo() << "Current m_shortBreakPeriod_min " << m_shortBreakPeriod_min;
    qInfo() << "Current m_workPeriod_min " << m_workPeriod_min;
    m_onBreak = breakness;
    emit breakChanged();
    m_ultradianModeRequested = qml_ultradianModeRequested;
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
    // These setters set the default values (not the same as the ones in start())
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


            /* You can run eye timer independently of workTimer, but when work timer's over,
             * stop the eye timer as well */
            /* EyeTimer *eyeTimer;
            eyeTimer->eyeTimerReset(); */
            // emit eyeBreakChanged(); // The called function should handle the private signal

            // But this all seems impossible. The interconnection should be in main.cpp,
            // but since that's mostly a placeholder for the QML, make the connection in main.qml's shared instance
            // with connections

            emit eyeTimerReset_from_timerManager();

            emit counterUpdated();
            emit breakChanged();
            emit sessionComplete();
            //m_ultradianMode = false;
            //emit ultradianModeChanged();
            m_ultradianModeRequested = false;
            //emit ultradianModeRequestChanged();
            //elapsed->restart();

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

