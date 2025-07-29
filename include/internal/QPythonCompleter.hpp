#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <verdigris>

/**
 * @brief Class, that describes completer with
 * glsl specific types and functions.
 */
class QPythonCompleter : public QCompleter
{
    W_OBJECT(QPythonCompleter)

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QPythonCompleter(QObject *parent = nullptr);
};
