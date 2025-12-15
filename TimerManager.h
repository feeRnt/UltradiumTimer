// SPDX-License-Identifier: GPL-3.0-only
/* TimerManager.h - Handle the timer functions for the work-break scheduling
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


// TimerManager.h
#pragma once //include only once in compilation

#include <QObject>
#include <QTimer>
//#include <QElapsedTimer>
#include <QMediaPlayer>
#include <QAudioOutput>

class TimerManager : public QObject { // A class TimerManager, inherited characteristics from QObject object
    Q_OBJECT
    Q_PROPERTY(int remainingTime READ remainingTime NOTIFY timeUpdated)
    Q_PROPERTY(bool onBreak READ onBreak NOTIFY breakChanged)
    Q_PROPERTY(bool ultradianModeOn READ ultradianModeOn NOTIFY ultradianModeChanged)
    Q_PROPERTY(int counter READ counter NOTIFY counterUpdated)
    Q_PROPERTY(float workPeriod_min READ workPeriod_min NOTIFY workPeriodChanged)
    Q_PROPERTY(float shortBreakPeriod_min READ shortBreakPeriod_min NOTIFY shortBreakPeriodChanged)
    Q_PROPERTY(float longBreakPeriod_min READ longBreakPeriod_min NOTIFY longBreakPeriodChanged)
//    Q_PROPERTY(qint64 elapsed_time_minute READ elapsed_time_minute() NOTIFY elapsedTimeChanged)

    //Q_Properties are vars that can be accessed from QML.
    //This is done by impelementing a C++ getter function, which returns the Class's internal variable

public:
    explicit TimerManager(QObject *parent = nullptr);

    Q_INVOKABLE void start(float workDuration, float breakDuration, bool ultradianMode, bool breakNess, int counter);
    Q_INVOKABLE void stop();
    Q_INVOKABLE void reset();
    //Q_INVOKABLE void memberVarSetter(float &m_var, float var_value); Does not work with QML,
    //as it doesn't know about pointers or references, except QObject
    Q_INVOKABLE void m_shortBreakPeriod_minSetter(float m_shortBreakPeriod_minSet);
    Q_INVOKABLE void m_longBreakPeriod_minSetter(float m_longBreakPeriod_minSet);
    Q_INVOKABLE void m_workPeriod_minSetter(float m_workPeriod_minSet);
//    Q_INVOKABLE qint64 elapsed_time_minute();

    int remainingTime() const { return m_remainingTime; }
    bool onBreak() const { return m_onBreak; }
    int counter() const { return m_counter; }
    bool ultradianModeOn() const { return m_ultradianModeOn; }

    float workPeriod_min() const { return m_workPeriod_min; }
    float shortBreakPeriod_min() const { return m_shortBreakPeriod_min; }
    float longBreakPeriod_min() const { return m_longBreakPeriod_min; }
    /*QMediaPlayer sfxPlayer;
    QAudioOutput sfxOutput;
    */
    QMediaPlayer* sfxPlayer;
    QAudioOutput* sfxOutput;

//    QElapsedTimer* elapsed;

//    qint64 elapsed_time_minute() const { return (elapsed->elapsed())/1000*60; }

signals:
    void timeUpdated();
    void breakChanged();
    void sessionComplete();
    void counterUpdated();
    void ultradianModeChanged();
    void workPeriodChanged();
    void shortBreakPeriodChanged();
    void longBreakPeriodChanged();
    void elapsedTimeChanged();

private slots:
    void updateTime();

private:
    QTimer m_timer;
    int m_remainingTime;
    int m_workDuration;
    int m_breakDuration;
    bool m_ultradianModeOn; //things that are always in memory
    int m_counter;
    bool m_onBreak;
    bool onPause;
    bool m_ultradianModeRequested;

    //    QString longBreakSFX = "231970__copyc4t__ding-4-secs-faded.flac";
    QString longBreakSFX = "qrc:/sound_resources/231970__copyc4t__ding-4-secs-faded.flac";
    QString shortBreakSFX = "qrc:/sound_resources/515643__mashedtatoes2__ding2.wav";
    QString workPeriodSFX = "qrc:/sound_resources/515612__mashedtatoes2__ding1.wav";

    float m_workPeriod_min;
    float m_shortBreakPeriod_min; // the defaults are initialized in timerManager.cpp
    float m_longBreakPeriod_min;
};
