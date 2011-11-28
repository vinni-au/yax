#include "rulesdelegate.hpp"

RulesDelegate::RulesDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{   }

QWidget* RulesDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    RulesTreeItem* item = reinterpret_cast<RulesTreeItem*>(index.internalPointer());
    if (item->type() == RulesTreeItem::Premise || item->type() == RulesTreeItem::Conclusion) {
        PremiseConclusionEditor* w = new PremiseConclusionEditor;
        w->setFocusPolicy(Qt::StrongFocus);
        w->setParent(parent);
        return w;
    } else return QStyledItemDelegate::createEditor(parent, option, index);
}

QSize RulesDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize result;
    RulesTreeItem* item = reinterpret_cast<RulesTreeItem*>(index.internalPointer());
    if (item->type() == RulesTreeItem::Premise || item->type() == RulesTreeItem::Conclusion) {
        result.setHeight(25);
    } else result.setHeight(15);
    return result;
}

/*
bool RulesDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index)
{
    return QAbstractItemDelegate::editorEvent(event, model, option, index);
}*/

PremiseConclusionEditor::PremiseConclusionEditor(QWidget *parent) :
    QWidget(parent)
{
    m_cbVariable = new QComboBox;
    m_cbValue = new QComboBox;
    QLabel* l = new QLabel(" = ");
    QHBoxLayout* layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_cbVariable);
    layout->addWidget(l);
    layout->addWidget(m_cbValue);
    layout->addStretch();
    setLayout(layout);
}
