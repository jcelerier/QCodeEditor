#pragma once

// QCodeEditor
#include <QHighlightBlockRule>
#include <QHighlightRule>
#include <QStyleSyntaxHighlighter> // Required for inheritance

// Qt
#include <QMap>
#include <QRegularExpression>
#include <QVector>
#include <verdigris>

class QSyntaxStyle;

/**
 * @brief Class, that describes C++ code
 * highlighter.
 */
class QLuaHighlighter : public QStyleSyntaxHighlighter
{
    W_OBJECT(QLuaHighlighter)
  public:
    /**
     * @brief Constructor.
     * @param document Pointer to document.
     */
    explicit QLuaHighlighter(QTextDocument *document = nullptr);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    QVector<QHighlightRule> m_highlightRules;
    QVector<QHighlightBlockRule> m_highlightBlockRules;

    QRegularExpression m_requirePattern;
    QRegularExpression m_functionPattern;
    QRegularExpression m_defTypePattern;
};
