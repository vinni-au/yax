#ifndef DOMAINDELETECOMMAND_HPP
#define DOMAINDELETECOMMAND_HPP

#include <QUndoCommand>

class DomainDeleteCommand : public QUndoCommand
{
public:
    DomainDeleteCommand();
};

#endif // DOMAINDELETECOMMAND_HPP
