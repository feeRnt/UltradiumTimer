// TimerManager.h
#pragma once //include only once in compilation

#include <QObject>
#include <QTimer>

class TimerManager : public QObject { // A class TimerManager, inherited characteristics from QObject object
    Q_OBJECT
    Q_PROPERTY(int remainingTime READ remainingTime NOTIFY timeUpdated)
    Q_PROPERTY(bool onBreak READ onBreak NOTIFY breakChanged)

public:
    explicit TimerManager(QObject *parent = nullptr);

    Q_INVOKABLE void start(float workDuration, float breakDuration, bool ultradianMode);
    Q_INVOKABLE void stop();

    int remainingTime() const { return m_remainingTime; }
    bool onBreak() const { return m_onBreak; }

signals:
    void timeUpdated();
    void breakChanged();
    void sessionComplete();

private slots:
    void updateTime();

private:
    QTimer m_timer;
    int m_remainingTime;
    int m_workDuration;
    int m_breakDuration;
    bool m_onBreak;
    bool m_ultradian;
};


