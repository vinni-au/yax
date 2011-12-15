#include "commandstack.hpp"

CommandStack* CommandStack::m_instance = 0;

CommandStack::CommandStack()
{
    m_stack = new QUndoStack;
}

CommandStack* CommandStack::instance()
{
    if (!m_instance)
        m_instance = new CommandStack;
    return m_instance;
}
