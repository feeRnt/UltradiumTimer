// TimerManager.cpp
#include "TimerManager.h"
#include <QDebug>

TimerManager::TimerManager(QObject *parent)
    : QObject(parent), m_remainingTime(0), m_onBreak(true)
{
    connect(&m_timer, &QTimer::timeout, this, &TimerManager::updateTime);
}

int counter = 0;

void TimerManager::start(float workDuration, float breakDuration, bool ultradianMode)
{
    m_workDuration = workDuration * 60;
    m_breakDuration = breakDuration * 60;
    m_onBreak = false;
    m_ultradian = ultradianMode;
    //m_remainingTime = m_workDuration;
    m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
    m_timer.start(1000); //rate of decrease
    emit breakChanged();
}

void TimerManager::stop()
{
    m_timer.stop();
    //m_remainingTime = 0;
    m_onBreak = true;
    emit timeUpdated();
    emit breakChanged();
}

void TimerManager::updateTime()
{
    m_remainingTime--;
    emit timeUpdated();

    if (m_remainingTime <= 0) {
        qInfo() << "time ran out. current counter = " << counter;
        counter = counter + 1;
        if (counter == 3) {
            qInfo() << "3 work periods in a row";
            m_onBreak = !m_onBreak;
            m_remainingTime = m_onBreak ? 30*60 : 25*60;
            counter = 0;
            emit breakChanged();
            emit sessionComplete();
        }
        else {
        m_onBreak = !m_onBreak;
        m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
        emit breakChanged();
        emit sessionComplete();
        }
    }
}

