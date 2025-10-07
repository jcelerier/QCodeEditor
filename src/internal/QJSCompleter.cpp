// QCodeEditor
#include <QLanguage>
#include <QJSCompleter>

// Qt
#include <QFile>
#include <QStringListModel>
#include <QMetaObject>
#include <QMetaMethod>
#include <QMetaProperty>

#include <wobjectimpl.h>
W_OBJECT_IMPL(QJSCompleter)

QJSCompleter::QJSCompleter(QObject *parent) : QCompleter(parent)
{
    // Setting up JavaScript types
    Q_INIT_RESOURCE(qcodeeditor_resources);
    QFile fl(":/languages/js.xml");

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
        m_baseCompletions.append(names);
    }

    m_model = new QStringListModel(this);
    setModel(m_model);
    updateCompletions();

    setCompletionColumn(0);
    setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    setCaseSensitivity(Qt::CaseSensitive);
    setWrapAround(true);
}

void QJSCompleter::registerObject(const QString& name, QObject* object)
{
    if (!object)
        return;

    // Get the meta-object for introspection
    const QMetaObject* metaObj = object->metaObject();

    // Extract all properties
    m_registeredCompletions.reserve(metaObj->propertyCount() + metaObj->methodCount());
    for (int i = 0; i < metaObj->propertyCount(); ++i)
    {
        m_registeredCompletions.append(QStringLiteral("%1.%2").arg(name, metaObj->property(i).name()));
    }

    // Extract all methods (slots, signals, and invokable methods)
    for (int i = 0; i < metaObj->methodCount(); ++i)
    {
        QMetaMethod method = metaObj->method(i);
        auto methodName = method.name();

        // Skip internal Qt methods
        if (methodName.startsWith("_q_"))
            continue;
        if (methodName.startsWith("destroyed") || methodName.startsWith("deleteLater"))
            continue;

        m_registeredCompletions.append(QStringLiteral("%1.%2").arg(name, methodName));
    }

    updateCompletions();
}

void QJSCompleter::unregisterObject(const QString& name)
{
    // Remove all completions that start with "name."
    QString prefix = name + ".";
    m_registeredCompletions.erase(
        std::remove_if(m_registeredCompletions.begin(), m_registeredCompletions.end(),
            [&prefix](const QString& completion) {
                return completion.startsWith(prefix);
            }),
        m_registeredCompletions.end()
    );

    updateCompletions();
}

void QJSCompleter::updateCompletions()
{
    QStringList allCompletions = m_baseCompletions;
    allCompletions.append(m_registeredCompletions);
    allCompletions.removeDuplicates();

    if (m_model)
        m_model->setStringList(allCompletions);
}
