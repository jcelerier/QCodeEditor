// QCodeEditor
#include <QLanguage>
#include <QFaustCompleter>

// Qt
#include <QFile>
#include <QStringListModel>

QFaustCompleter::QFaustCompleter(QObject *parent) : QCompleter(parent)
{
    // Setting up Faust types and functions
    QStringList list;

    Q_INIT_RESOURCE(qcodeeditor_resources);
    QFile fl(":/languages/faust.xml");

    if (!fl.open(QIODevice::ReadOnly))
    {
        return;
    }

    QLanguage language(&fl);

    if (language.isLoaded())
    {
        auto keys = language.keys();
        qDebug() << keys;
        for (auto &&key : keys)
        {
            auto names = language.names(key);
            list.append(names);
        }
    }

    setModel(new QStringListModel(list, this));
    setCompletionColumn(0);
    setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    setCaseSensitivity(Qt::CaseSensitive);
    setWrapAround(true);
}
