#include "EyeTimer.h"

EyeTimer::EyeTimer(QObject *parent)
    : QObject{parent}, m_eyeTimerRemainingTime(0), m_onEyeBreak(false),
    m_eyeTimerBreakDuration_default(0.5), m_eyeTimerDuration_default(5)
{
    connect(&m_eyeTimer, &QTimer::timeout, this, &EyeTimer::updateEyeTimer);

    eyeTimer_sfxPlayer = new QSoundEffect(this);
    eyeTimer_sfxPlayer->setVolume(1);
}

void EyeTimer::eyeTimerStart(float qml_eyeTimerDuration, float qml_eyeTimerBreakDuration, bool qml_eyeTimerBreakness)
{
    m_eyeTimerDuration = qml_eyeTimerDuration;
    m_eyeTimerBreakDuration = qml_eyeTimerBreakDuration;
    m_onEyeBreak = qml_eyeTimerBreakness;

    emit eyeBreakChanged();
    m_eyeTimerRemainingTime = m_onEyeBreak ? m_eyeTimerBreakDuration * 60 : m_eyeTimerDuration * 60;
    m_eyeTimer.start(1000); /* int msec - timeout interval */
}

void EyeTimer::eyeTimerStop()
{
    m_eyeTimer.stop();
    emit eyeTimerUpdated();
}

void EyeTimer::eyeTimerReset()
{
    m_eyeTimer.stop();
    m_eyeTimerRemainingTime = 0;
    m_eyeTimerDuration = 0;
    m_eyeTimerBreakDuration = 0;
    m_onEyeBreak = true;

    emit eyeTimerUpdated();
    emit eyeBreakChanged();
}

/* TODO: Implement in QML and EyeTimer.h
void EyeTimer::eyeTimer_timerSetter(float qml_eyeTimerSetTimerDuration)
{
    m_eyeTimerBreakDuration = qml_eyeTimerSetTimerDuration;
}

void EyeTimer::eyeTimer::m_longBreakPeriod_minSetter(float qml_eyeTimerSetBreakDuration)
{
    m_eyeTimerDuration = qml_eyeTimerSetBreakDuration;
    //remove set? One & same parameter as eyeTimerStart?
} */

void EyeTimer::updateEyeTimer()
{
    m_eyeTimerRemainingTime--;
    emit eyeTimerUpdated();

    if (m_eyeTimerRemainingTime <= 0) {
        m_onEyeBreak = !m_onEyeBreak;

        eyeTimer_sfxPlayer->setSource(QUrl((m_onEyeBreak ? eyeBreakStartSFX : eyeBreakEndSFX)));
        eyeTimer_sfxPlayer->play();

        m_eyeTimerRemainingTime = m_onEyeBreak ? m_eyeTimerBreakDuration * 60 : m_eyeTimerDuration * 60;
        emit eyeBreakChanged();
    }

}
