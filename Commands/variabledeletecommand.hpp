#ifndef VARIABLEDELETECOMMAND_HPP
#define VARIABLEDELETECOMMAND_HPP

#include <QUndoCommand>

class VariableDeleteCommand : public QUndoCommand
{
public:
    VariableDeleteCommand();
};

#endif // VARIABLEDELETECOMMAND_HPP
