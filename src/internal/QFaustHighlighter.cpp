// QCodeEditor
#include <QFaustHighlighter>
#include <QLanguage>
#include <QSyntaxStyle>

// Qt
#include <QFile>

QFaustHighlighter::QFaustHighlighter(QTextDocument *document)
    : QStyleSyntaxHighlighter(document), m_highlightRules(),
      m_includePattern(QRegularExpression(R"_(^\s*import\s*\(\s*"([^"]+)"\s*\)\s*;)_")),
      m_functionPattern(QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*)\s*\([^)]*\)\s*=)")),
      m_defTypePattern(QRegularExpression(R"(\b([_a-zA-Z][_a-zA-Z0-9]*)\s*=\s*[^=])")),
      m_processPattern(QRegularExpression(R"(\bprocess\b)")), m_withPattern(QRegularExpression(R"(\bwith\s*\{)")),
      m_environmentPattern(QRegularExpression(R"(\benvironment\s*\{)")),
      m_libraryPattern(QRegularExpression(R"_(\blibrary\s*\(\s*"([^"]+)"\s*\))_")),
      m_componentPattern(QRegularExpression(R"_(\bcomponent\s*\(\s*"([^"]+)"\s*\))_")),
      m_declarePattern(QRegularExpression(R"(\bdeclare\s+[_a-zA-Z][_a-zA-Z0-9]*\s+"[^"]*")")),
      m_metadataPattern(QRegularExpression(R"(\[[^\]]+\])")), m_commentStartPattern(QRegularExpression(R"(/\*)")),
      m_commentEndPattern(QRegularExpression(R"(\*/)"))
{
    Q_INIT_RESOURCE(qcodeeditor_resources);
    QFile fl(":/languages/faust.xml");

    if (!fl.open(QIODevice::ReadOnly))
    {
        return;
    }

    QLanguage language(&fl);

    if (!language.isLoaded())
    {
        return;
    }

    auto keys = language.keys();
    for (auto &&key : keys)
    {
        auto names = language.names(key);
        for (auto &&name : names)
        {
            m_highlightRules.append({QRegularExpression(QString(R"(\b%1\b)").arg(name)), key});
        }
    }
    // Mathematical operators
    m_highlightRules.append({QRegularExpression(R"((\+|-|\*|/|%|\^|&|\||<<|>>|@|'))"), "Operator"});

    // Comparison operators
    m_highlightRules.append({QRegularExpression(R"((==|!=|<|>|<=|>=))"), "Operator"});

    // Parens
    m_highlightRules.append({QRegularExpression(R"([\(\)])"), "JsScopeVar"});

    // Faust operators
    m_highlightRules.append({QRegularExpression(R"((<:|:>|,|:|~))"), "VisualWhitespace"});

    // Special symbols
    m_highlightRules.append({QRegularExpression(R"((\b_\b|\!))"), "Keyword"});

    // Metadata tags
    m_highlightRules.append(
        {QRegularExpression(R"(</?(?:mdoc|equation|diagram|metadata|notice|listing)>)"), "Preprocessor"});

    // Numbers (including floats and scientific notation)
    m_highlightRules.append(
        {QRegularExpression(R"(((?<=\b|\s|^)(?i)(?:\d+(?:\.\d*)?|\.\d+)(?:e[+-]?\d+)?(?=\b|\s|$)))"), "Number"});

    // Single line comments
    m_highlightRules.append({QRegularExpression(R"(//[^\n]*)"), "Comment"});

    // Strings
    m_highlightRules.append({QRegularExpression(R"(".*?")", QRegularExpression::DotMatchesEverythingOption |
                                                                QRegularExpression::MultilineOption),
                             "String"});

    // Comment sequences for toggling support
    m_commentLineSequence = "//";
    m_startCommentBlockSequence = "/*";
    m_endCommentBlockSequence = "*/";
}

void QFaustHighlighter::highlightBlock(const QString &text)
{
    // Checking for import
    {
        auto matchIterator = m_includePattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat("Keyword"));

            setFormat(match.capturedStart(1), match.capturedLength(1), syntaxStyle()->getFormat("String"));
        }
    }

    // Checking for library
    {
        auto matchIterator = m_libraryPattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat("Keyword"));

            setFormat(match.capturedStart(1), match.capturedLength(1), syntaxStyle()->getFormat("String"));
        }
    }

    // Checking for component
    {
        auto matchIterator = m_componentPattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat("Keyword"));

            setFormat(match.capturedStart(1), match.capturedLength(1), syntaxStyle()->getFormat("String"));
        }
    }

    // Checking for declare statements
    {
        auto matchIterator = m_declarePattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat("Preprocessor"));
        }
    }

    // Checking for function definitions
    {
        auto matchIterator = m_functionPattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(1), match.capturedLength(1), syntaxStyle()->getFormat("Function"));
        }
    }

    // Checking for simple definitions
    {
        auto matchIterator = m_defTypePattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(1), match.capturedLength(1), syntaxStyle()->getFormat("Type"));
        }
    }

    // Checking for metadata in UI elements
    {
        auto matchIterator = m_metadataPattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat("Preprocessor"));
        }
    }

    // Apply general highlight rules
    for (auto &rule : m_highlightRules)
    {
        auto matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext())
        {
            auto match = matchIterator.next();

            setFormat(match.capturedStart(), match.capturedLength(), syntaxStyle()->getFormat(rule.formatName));
        }
    }

    // Handle multi-line comments
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = text.indexOf(m_commentStartPattern);
    }

    while (startIndex >= 0)
    {
        auto match = m_commentEndPattern.match(text, startIndex);

        int endIndex = match.capturedStart();
        int commentLength = 0;

        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + match.capturedLength();
        }

        setFormat(startIndex, commentLength, syntaxStyle()->getFormat("Comment"));
        startIndex = text.indexOf(m_commentStartPattern, startIndex + commentLength);
    }
}
