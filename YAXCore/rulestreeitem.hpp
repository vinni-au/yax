#ifndef RULESTREEITEM_HPP
#define RULESTREEITEM_HPP

#include <QVariant>
#include "yaxkb.hpp"

class RulesTreeItem
{
    friend class YAXRulesModel;

    Rule* m_rule;
    int m_type;
    bool m_fake;
    RulesTreeItem* m_parent;
    QList<RulesTreeItem*> m_children;

public:
    enum RulesTreeItemType {
        Root = -1,
        RuleName = 0,
        If,
        Then,
        Reason,
        Premise,
        Conclusion
    };

    RulesTreeItem(Rule* rule, int type = RuleName, RulesTreeItem* parent = 0, bool fake = false);
    ~RulesTreeItem();

    RulesTreeItem* child(int n) const;

    RulesTreeItem* parent() const
    {   return m_parent;    }

    int childNumber() const;

    void addChild(RulesTreeItem* child)
    {   m_children << child;    }

    int childCount() const
    {   return m_children.count();  }

    QVariant data(int role) const;

    int type() const
    {   return m_type;  }

    bool isFake() const
    {   return m_fake;  }

    Rule* rule() const
    {   return m_rule;  }

    static RulesTreeItem* createBranch(Rule* rule);
};

#endif // RULESTREEITEM_HPP
