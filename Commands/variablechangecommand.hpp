#ifndef VARIABLECHANGECOMMAND_HPP
#define VARIABLECHANGECOMMAND_HPP

#include <QUndoCommand>

class VariableChangeCommand : public QUndoCommand
{
public:
    VariableChangeCommand();
};

#endif // VARIABLECHANGECOMMAND_HPP
