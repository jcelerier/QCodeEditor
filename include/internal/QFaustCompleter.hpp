#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <verdigris>

/**
 * @brief Class, that describes completer with
 * Faust specific types and functions.
 */
class QFaustCompleter : public QCompleter
{
    W_OBJECT(QFaustCompleter)

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QFaustCompleter(QObject *parent = nullptr);
};
