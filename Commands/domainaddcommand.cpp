#include "domainaddcommand.hpp"

DomainAddCommand::DomainAddCommand(QString name, int position, QUndoCommand *parent)
    : QUndoCommand(parent), m_name(name), m_position(position)
{
    setText("Добавлен домен '" + name + "' в позиции " + QString::number(position));
}


void DomainAddCommand::undo()
{

}

void DomainAddCommand::redo()
{

}
