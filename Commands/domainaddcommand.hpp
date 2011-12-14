#ifndef DOMAINADDCOMMAND_HPP
#define DOMAINADDCOMMAND_HPP

#include <QUndoCommand>
#include "./../YAXCore/yaxkb.hpp"

class DomainAddCommand : public QUndoCommand
{
    QString m_name;
    int m_position;

public:
    DomainAddCommand(QString name, int position, QUndoCommand* parent = 0);

    void undo();
    void redo();
};

#endif // DOMAINADDCOMMAND_HPP
