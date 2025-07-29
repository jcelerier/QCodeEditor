#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <verdigris>

/**
 * @brief Class, that describes completer with
 * glsl specific types and functions.
 */
class QGLSLCompleter : public QCompleter
{
    W_OBJECT(QGLSLCompleter)

  public:
    /**
     * @brief Constructor.
     * @param parent Pointer to parent QObject.
     */
    explicit QGLSLCompleter(QObject *parent = nullptr);
};
