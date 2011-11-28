#include "rulestreeitem.hpp"

RulesTreeItem::RulesTreeItem(Rule *rule, int type, RulesTreeItem *parent, bool fake) :
    m_rule(rule), m_type(type), m_parent(parent), m_fake(fake)
{   }

RulesTreeItem::~RulesTreeItem()
{
    qDeleteAll(m_children);
    m_children.clear();
}

RulesTreeItem* RulesTreeItem::child(int n) const
{
    if (n < m_children.count())
        return m_children.at(n);
    else return 0;
}

int RulesTreeItem::childNumber() const
{
    if (m_parent)
        return m_parent->m_children.indexOf(const_cast<RulesTreeItem*>(this));

    return 0;
}

QVariant RulesTreeItem::data(int role) const
{
    QVariant result;
    if (!m_fake) {
        switch (m_type)
        {
        case RuleName:
            result = QVariant(m_rule->name);
            break;
        case If:
            result = QVariant("еякх ");
            break;
        case Then:
            result = QVariant("рн ");
            break;
        case Reason:
            if (role == Qt::DisplayRole)
                result = QVariant("р.й. " + m_rule->reasoning);
            else if (role == Qt::EditRole)
                result = m_rule->reasoning;
            break;
        case Premise:
            if (role == Qt::DisplayRole) {
            int i = childNumber();
            result = QVariant(m_rule->premises.at(i)->variable->name + " = " +
                              m_rule->premises.at(i)->value->name);
            }
            break;
        case Conclusion:
            if (role == Qt::DisplayRole) {
            int i = childNumber();
            result = QVariant(m_rule->conclusions.at(i)->variable->name + " = " +
                              m_rule->conclusions.at(i)->value->name);
            }
            break;
        }
    } else result = QVariant("+");
    return result;
}

RulesTreeItem* RulesTreeItem::createBranch(Rule *rule)
{
    RulesTreeItem* root     = new RulesTreeItem(rule);
    RulesTreeItem* reason   = new RulesTreeItem(rule, Reason, root);
    RulesTreeItem* if_      = new RulesTreeItem(rule, If, root);
    RulesTreeItem* then_    = new RulesTreeItem(rule, Then, root);

    root->addChild(if_);
    root->addChild(then_);
    root->addChild(reason);

    for (int i = 0; i < rule->premises.count(); ++i) {
        RulesTreeItem* premise = new RulesTreeItem(rule, Premise, if_);
        if_->addChild(premise);
    }

    if_->addChild(new RulesTreeItem(rule, Premise, if_, true));

    for (int i = 0; i < rule->conclusions.count(); ++i) {
        RulesTreeItem* conclusion = new RulesTreeItem(rule, Conclusion, then_);
        then_->addChild(conclusion);
    }

    then_->addChild(new RulesTreeItem(rule, Conclusion, then_, true));

    return root;
}
