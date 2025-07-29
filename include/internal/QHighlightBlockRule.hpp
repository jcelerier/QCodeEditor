#pragma once

// Qt
#include <QRegularExpression>
#include <QString>
#include <verdigris>

struct QHighlightBlockRule
{
    QHighlightBlockRule() : startPattern(), endPattern(), formatName()
    {
    }

    QHighlightBlockRule(QRegularExpression start, QRegularExpression end, QString format)
        : startPattern(std::move(start)), endPattern(std::move(end)), formatName(std::move(format))
    {
    }

    QRegularExpression startPattern;
    QRegularExpression endPattern;
    QString formatName;
};
