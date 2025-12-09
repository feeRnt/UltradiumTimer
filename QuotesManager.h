#pragma once

#include <QObject>
#include <QStringList>

class QuotesManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString randomQuote READ randomQuote NOTIFY quoteChanged)
    //get Q-string by reading from function randomQuote. Afterwards
    //notify with quotesChanged's emitted signal

public: //accessed by all parts of the program. Qt, QML, cpp, etc.
    QuotesManager(const QString &filePath, QObject *parent = nullptr);
    // Class constructor; run when the class is initialized

    QString randomQuote();

signals: // an emitted "signal" when something happens within the program
         // qt specialty
    void quoteChanged();

private: // Only accessible by members of this class (QuotesManager).
    QStringList m_quotes;
};

