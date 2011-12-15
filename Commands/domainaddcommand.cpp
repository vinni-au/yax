#include "domainaddcommand.hpp"

DomainAddCommand::DomainAddCommand(QString name, int position, QUndoCommand *parent)
    : QUndoCommand(parent), m_name(name), m_position(position)
{
    setText("Добавлен домен '" + name + "' в позиции " + QString::number(position));
}


void DomainAddCommand::undo()
{
    yaxModels()->domainModel()->removeRow(m_position);
}

void DomainAddCommand::redo()
{
    YAXDomainsModel* model = yaxModels()->domainModel();
    model->insertRow(m_position);
    model->setData(model->index(m_position), m_name);
    model->dataChanged(model->index(m_position), model->index(model->domainsList().count()));
}
