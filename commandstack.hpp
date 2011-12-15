#ifndef COMMANDSTACK_HPP
#define COMMANDSTACK_HPP

#include <QObject>
#include <QUndoStack>

#define undoStack() (CommandStack::instance()->stack())

class CommandStack : public QObject
{
    Q_OBJECT

    static CommandStack* m_instance;
    CommandStack();

    QUndoStack* m_stack;
public:
    static CommandStack* instance();

    QUndoStack* stack()
    {   return m_stack; }

signals:

public slots:

};

#endif // COMMANDSTACK_HPP
