#include "QuotesManager.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>

QuotesManager::QuotesManager(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty())
                m_quotes << line;
        }
        file.close();
    } else {
        qWarning() << "Could not open quotes file:" << filePath;
    }
}

QString QuotesManager::randomQuote()
{
    if (m_quotes.isEmpty())
        return "No quotes found.";

    int index = QRandomGenerator::global()->bounded(m_quotes.size());
    return m_quotes.at(index);
}

