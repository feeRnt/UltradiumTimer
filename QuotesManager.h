#pragma once

#include <QObject>
#include <QStringList>

class QuotesManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString randomQuote READ randomQuote NOTIFY quoteChanged)

public:
    QuotesManager(const QString &filePath, QObject *parent = nullptr);

    QString randomQuote();

signals:
    void quoteChanged();

private:
    QStringList m_quotes;
};

