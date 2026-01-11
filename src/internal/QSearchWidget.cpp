#include <QSearchWidget>
#include <QCodeEditor>
#include <QSyntaxStyle>

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QStyle>

#include <wobjectimpl.h>
W_OBJECT_IMPL(QSearchWidget)

QSearchWidget::QSearchWidget(QCodeEditor *parent)
    : QWidget(parent)
    , m_codeEditor(parent)
    , m_searchInput(new QLineEdit(this))
    , m_prevButton(new QPushButton(this))
    , m_nextButton(new QPushButton(this))
    , m_closeButton(new QPushButton(this))
    , m_resultLabel(new QLabel(this))
    , m_syntaxStyle(nullptr)
{
    setVisible(false);

    // Setup layout
    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);

    // Search input
    m_searchInput->setPlaceholderText("Search...");
    m_searchInput->setMinimumWidth(200);

    // Buttons with text (no icons needed)
    m_prevButton->setText("<");
    m_prevButton->setFixedWidth(24);
    m_prevButton->setToolTip("Previous match (Shift+Enter)");

    m_nextButton->setText(">");
    m_nextButton->setFixedWidth(24);
    m_nextButton->setToolTip("Next match (Enter)");

    m_closeButton->setText("X");
    m_closeButton->setFixedWidth(24);
    m_closeButton->setToolTip("Close (Escape)");

    // Result label
    m_resultLabel->setMinimumWidth(60);

    // Add widgets to layout
    layout->addWidget(m_searchInput);
    layout->addWidget(m_resultLabel);
    layout->addWidget(m_prevButton);
    layout->addWidget(m_nextButton);
    layout->addWidget(m_closeButton);
    layout->addStretch();

    // Connect signals
    connect(m_searchInput, &QLineEdit::textChanged, this, &QSearchWidget::searchTextChanged);
    connect(m_searchInput, &QLineEdit::returnPressed, this, [this]() {
        Q_EMIT findNext();
    });
    connect(m_prevButton, &QPushButton::clicked, this, &QSearchWidget::findPrevious);
    connect(m_nextButton, &QPushButton::clicked, this, &QSearchWidget::findNext);
    connect(m_closeButton, &QPushButton::clicked, this, &QSearchWidget::hideSearch);
}

void QSearchWidget::setSyntaxStyle(QSyntaxStyle *style)
{
    m_syntaxStyle = style;
    updateStyle();
}

void QSearchWidget::updateStyle()
{
#ifndef QT_NO_STYLE_STYLESHEET
    if (m_syntaxStyle)
    {
        QString bgColor = m_syntaxStyle->getFormat("Text").background().color().name();
        QString textColor = m_syntaxStyle->getFormat("Text").foreground().color().name();
        QString borderColor = m_syntaxStyle->getFormat("LineNumber").foreground().color().name();

        setStyleSheet(QString(
            "QSearchWidget { background-color: %1; border-bottom: 1px solid %2; }"
            "QLineEdit { background-color: %1; color: %3; border: 1px solid %2; padding: 2px; }"
            "QPushButton { background-color: %1; color: %3; border: 1px solid %2; padding: 2px; }"
            "QPushButton:hover { background-color: %2; }"
            "QLabel { color: %3; }"
        ).arg(bgColor, borderColor, textColor));
    }
#endif
}

void QSearchWidget::showSearch()
{
    setVisible(true);
    m_searchInput->setFocus();
    m_searchInput->selectAll();
}

void QSearchWidget::hideSearch()
{
    setVisible(false);
    m_searchInput->clear();
    m_resultLabel->clear();
    m_codeEditor->setFocus();
    Q_EMIT searchClosed();
}

bool QSearchWidget::isSearchVisible() const
{
    return isVisible();
}

QString QSearchWidget::searchText() const
{
    return m_searchInput->text();
}

void QSearchWidget::updateResultCount(int current, int total)
{
    if (total == 0)
    {
        m_resultLabel->setText("No results");
    }
    else
    {
        m_resultLabel->setText(QString("%1 of %2").arg(current).arg(total));
    }
}

void QSearchWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        hideSearch();
        return;
    }

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        if (event->modifiers() & Qt::ShiftModifier)
        {
            Q_EMIT findPrevious();
        }
        else
        {
            Q_EMIT findNext();
        }
        return;
    }

    QWidget::keyPressEvent(event);
}
