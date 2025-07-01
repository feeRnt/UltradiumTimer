// TimerManager.cpp
#include "TimerManager.h"

TimerManager::TimerManager(QObject *parent)
    : QObject(parent), m_remainingTime(0), m_onBreak(false)
{
    connect(&m_timer, &QTimer::timeout, this, &TimerManager::updateTime);
}

void TimerManager::start(int workDuration, int breakDuration, bool ultradianMode)
{
    m_workDuration = workDuration * 60;
    m_breakDuration = breakDuration * 60;
    m_onBreak = false;
    m_ultradian = ultradianMode;
    m_remainingTime = m_workDuration;
    m_timer.start(1000);
    emit breakChanged();
}

void TimerManager::stop()
{
    m_timer.stop();
    m_remainingTime = 0;
    emit timeUpdated();
}

void TimerManager::updateTime()
{
    m_remainingTime--;
    emit timeUpdated();

    if (m_remainingTime <= 0) {
        m_onBreak = !m_onBreak;
        m_remainingTime = m_onBreak ? m_breakDuration : m_workDuration;
        emit breakChanged();
        emit sessionComplete();
    }
}

