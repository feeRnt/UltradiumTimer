// TimerManager.cpp
#include "TimerManager.h"
#include <QDebug>

TimerManager::TimerManager(QObject *parent)
    : QObject(parent), m_remainingTime(0), m_onBreak(true)
{
    connect(&m_timer, &QTimer::timeout, this, &TimerManager::updateTime);
}

int counter = 0;
bool onPause = true;

void TimerManager::start(float workDuration, float breakDuration, bool ultradianMode, bool breakNess)
{
    m_workDuration = workDuration * 60;
    m_breakDuration = breakDuration * 60;
    m_onBreak = breakNess;
    emit breakChanged();
    //m_ultradian = ultradianMode;
    //m_remainingTime = m_workDuration;
    //qInfo() << "Current m_onBreak = " << m_onBreak;
    m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
    m_timer.start(1000); //rate of decrease
}

void TimerManager::stop()
{
    m_timer.stop();
    //m_remainingTime = 0;
    //m_onBreak = true;
    emit timeUpdated();
    //emit breakChanged();
}

void TimerManager::updateTime()
{
    m_remainingTime--;
    emit timeUpdated();

    if (m_remainingTime <= 0) {
        //qInfo() << "time ran out. current counter = " << counter;
        if (!m_onBreak) {
            counter = counter + 1;
        }
        if (counter == 3) { // 1 - based. Use 6, and assign to - 1 without !onBreak check
            qInfo() << "3 work periods in a row";
            m_onBreak = !m_onBreak;
            //m_remainingTime = m_onBreak ? 30*60 : 25*60;
            //m_onBreak = true;
            m_remainingTime = 35*60;
            counter = 0;
            emit breakChanged();
            emit sessionComplete();
        }
        else {
        m_onBreak = !m_onBreak;
        //m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
        m_remainingTime = m_onBreak ? 5*60 : 25*60;
        emit breakChanged();
        emit sessionComplete();
        }
    }
}

