#pragma once

// Qt
#include <QCompleter> // Required for inheritance

/**
 * @brief Class, that describes completer with
 * Faust specific types and functions.
 */
class QFaustCompleter : public QCompleter
{
    Q_OBJECT

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QFaustCompleter(QObject *parent = nullptr);
};