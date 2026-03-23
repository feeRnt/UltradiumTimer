#pragma once

#ifndef EYETIMER_H
#define EYETIMER_H

#include <QObject>
#include <QTimer>

#include <QSoundEffect>

class EyeTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float eyeTimerRemainingTime READ eyeTimerRemainingTime NOTIFY eyeTimerUpdated)
    Q_PROPERTY(float eyeTimerDuration READ eyeTimerDuration)
    Q_PROPERTY(float eyeTimerBreakDuration READ eyeTimerBreakDuration)

    Q_PROPERTY(float eyeTimerDuration_default READ eyeTimerDuration_default)
    Q_PROPERTY(float eyeTimerBreakDuration_default READ eyeTimerBreakDuration_default)

    Q_PROPERTY(bool onEyeBreak READ onEyeBreak NOTIFY eyeBreakChanged)
    /* Q_PROPERTY(float eyeTimerBreakDuration READ eyeTimerBreakDuration) */

public:
    explicit EyeTimer(QObject *parent = nullptr);

    // Just calling this function is easier for us now than having a separate setter function
    Q_INVOKABLE void eyeTimerStart(float qml_eyeTimerTime, float qml_eyeTimerBreakTime, bool qml_eyeTimerBreakness);
    Q_INVOKABLE void eyeTimerStop();
    Q_INVOKABLE void eyeTimerReset();

    float eyeTimerRemainingTime() const { return m_eyeTimerRemainingTime; }
    float eyeTimerDuration() const { return m_eyeTimerDuration; }
    float eyeTimerBreakDuration() const { return m_eyeTimerBreakDuration; }

    float eyeTimerDuration_default() const { return m_eyeTimerDuration_default; }
    float eyeTimerBreakDuration_default() const { return m_eyeTimerBreakDuration_default; }

    bool onEyeBreak() const { return m_onEyeBreak; }
    /* float eyeTimerBreakDuration() const { return m_eyeTimerBreakDuration; } */

    QSoundEffect* eyeTimer_sfxPlayer;

signals:
    void eyeBreakChanged();
    void eyeTimerUpdated();

private slots:
    void updateEyeTimer();

private:
    QTimer m_eyeTimer;

    /* All in minutes */
    float m_eyeTimerDuration;
    float m_eyeTimerBreakDuration;
    float m_eyeTimerRemainingTime;

    float m_eyeTimerDuration_default;
    float m_eyeTimerBreakDuration_default;

    bool m_onEyeBreak;

    QString eyeBreakStartSFX = "qrc:/sound_resources/Eye Intro.wav";
    QString eyeBreakEndSFX = "qrc:/sound_resources/Eye Outro.wav";
};

#endif // EYETIMER_H
