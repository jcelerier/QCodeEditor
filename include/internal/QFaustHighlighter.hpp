#pragma once

// QCodeEditor
#include <QHighlightRule>
#include <QStyleSyntaxHighlighter> // Required for inheritance

// Qt
#include <QRegularExpression>
#include <QVector>

class QSyntaxStyle;

/**
 * @brief Class, that describes Faust code
 * highlighter.
 */
class QFaustHighlighter : public QStyleSyntaxHighlighter
{
    Q_OBJECT
  public:
    /**
     * @brief Constructor.
     * @param document Pointer to document.
     */
    explicit QFaustHighlighter(QTextDocument *document = nullptr);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    QVector<QHighlightRule> m_highlightRules;

    QRegularExpression m_includePattern;
    QRegularExpression m_functionPattern;
    QRegularExpression m_defTypePattern;
    QRegularExpression m_processPattern;
    QRegularExpression m_withPattern;
    QRegularExpression m_environmentPattern;
    QRegularExpression m_libraryPattern;
    QRegularExpression m_componentPattern;
    QRegularExpression m_declarePattern;
    QRegularExpression m_metadataPattern;

    QRegularExpression m_commentStartPattern;
    QRegularExpression m_commentEndPattern;
};