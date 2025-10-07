#pragma once

// Qt
#include <QCompleter> // Required for inheritance
#include <QStringList>
#include <verdigris>

class QObject;
class QStringListModel;

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

    /**
     * @brief Register a QObject instance to make its properties and methods available for completion.
     * @param name The name/prefix used to access this object in JavaScript (e.g., "Foo" for "Foo.method()")
     * @param object The QObject instance whose meta-object will be introspected
     */
    void registerObject(const QString& name, QObject* object);

    /**
     * @brief Unregister a previously registered object.
     * @param name The name of the object to unregister
     */
    void unregisterObject(const QString& name);

  private:
    void updateCompletions();

    QStringList m_baseCompletions;
    QStringList m_registeredCompletions;
    QStringListModel* m_model = nullptr;
};
