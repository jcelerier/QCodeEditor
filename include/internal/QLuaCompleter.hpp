#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <verdigris>

/**
 * @brief Class, that describes completer with
 * glsl specific types and functions.
 */
class QLuaCompleter : public QCompleter
{
    W_OBJECT(QLuaCompleter)

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QLuaCompleter(QObject *parent = nullptr);
};
