#ifndef RULESDELEGATE_HPP
#define RULESDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QtGui>
#include <QSize>
#include "rulestreeitem.hpp"
#include "yaxmodels.hpp"

class RulesDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit RulesDelegate(QObject *parent = 0);

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //virtual bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:

public slots:

};

class PremiseConclusionEditor : public QWidget
{
    Q_OBJECT

    QComboBox* m_cbVariable;
    QComboBox* m_cbValue;
public:
    explicit PremiseConclusionEditor(QWidget* parent = 0);

};

#endif // RULESDELEGATE_HPP
