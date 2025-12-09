#include "QuotesManager.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>

QuotesManager::QuotesManager(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    QFile file(filePath);

    //qInfo() << "hello?";
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
    // qInfo() << "All quotes are: " << m_quotes;
    /*
     * qInfo() << "Printing nth line of quotesfile. n = " << index;
     * qInfo() << "It will be this: " << m_quotes.at(index);
    */
    return m_quotes.at(index);
}

