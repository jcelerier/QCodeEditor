#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <verdigris>

/**
 * @brief Class, that describes completer with
 * javascript specific types and functions.
 */
class QJSCompleter : public QCompleter
{
    W_OBJECT(QJSCompleter)

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QJSCompleter(QObject *parent = nullptr);
};
