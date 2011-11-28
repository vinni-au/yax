#include "yaxrulesmodel.hpp"

YAXRulesModel::YAXRulesModel(QObject *parent) :
    QAbstractItemModel(parent), m_root(new RulesTreeItem(0, -1))
{
    Premise* premise = new Premise(new Variable("olol", new Domain("oolo")), new Value("v"));
    Conclusion* conclusion = new Conclusion(new Variable("рост", new Domain("oolo")), new Value("выше среднего"));
    addRule(new Rule("правило 1", "гладиолус 1",
                     QList<Premise*>() << premise,
                     QList<Conclusion*>() << conclusion));
    addRule(new Rule("правило 2", "гладиолус 2"));
    addFakeRule();
}

YAXRulesModel::~YAXRulesModel()
{
    delete m_root;
}

void YAXRulesModel::setRoot(RulesTreeItem *root)
{
    delete m_root;
    m_root = root;
    reset();
}

int YAXRulesModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

int YAXRulesModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return m_root->childCount();
    RulesTreeItem* parentItem = itemFromIndex(parent);
    if (!parentItem)
        return 0;
    int result = parentItem->childCount();
    return result;
}

QModelIndex YAXRulesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!m_root)
        return QModelIndex();

    if (parent == QModelIndex())
        if (row < m_root->childCount())
            return createIndex(row, column, m_root->m_children[row]);
        else return QModelIndex();

    RulesTreeItem* parentItem = itemFromIndex(parent);
    if (row < parentItem->childCount())
        return createIndex(row, column, parentItem->m_children[row]);
    return QModelIndex();
}

QModelIndex YAXRulesModel::parent(const QModelIndex &child) const
{
    RulesTreeItem* item = itemFromIndex(child);
    if (!item)
        return QModelIndex();
    RulesTreeItem* parentItem = item->parent();
    if (!parentItem)
        return QModelIndex();
    RulesTreeItem* grandParent = parentItem->parent();
    if (!grandParent)
        grandParent = m_root;

    int row = grandParent->m_children.indexOf(parentItem);
    return createIndex(row, child.column(), parentItem);
}

QVariant YAXRulesModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    RulesTreeItem* item = itemFromIndex(index);
    if (!item)
        return QVariant();

    if (index.column() == 0)
        return item->data(role);

    return QVariant();
}

Qt::ItemFlags YAXRulesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    if (index.isValid()) {
        RulesTreeItem* item = itemFromIndex(index);
        if (item->type() != RulesTreeItem::If &&
                item->type() != RulesTreeItem::Then)
        return (result | Qt::ItemIsEditable);
        else return result;
    } else return result;
}

bool YAXRulesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

RulesTreeItem* YAXRulesModel::itemFromIndex(const QModelIndex& index) const
{
    if (index.isValid())
        return reinterpret_cast<RulesTreeItem*>(index.internalPointer());
    return m_root;
}

void YAXRulesModel::addRule(Rule *rule, int index)
{
    if (index == -1)
        m_rulesList << rule;
    else m_rulesList.insert(index, rule);

    RulesTreeItem* newItem = RulesTreeItem::createBranch(rule);

    if (index == -1)
        m_root->m_children << newItem;
    else m_root->m_children.insert(index, newItem);
}

void YAXRulesModel::addFakeRule()
{
    RulesTreeItem* item = new RulesTreeItem(new Rule(), RulesTreeItem::RuleName, 0, true);
    m_root->addChild(item);
}
