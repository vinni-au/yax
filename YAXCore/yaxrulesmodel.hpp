#ifndef YAXRULESMODEL_HPP
#define YAXRULESMODEL_HPP

#include <QAbstractItemModel>
#include "rulestreeitem.hpp"

class YAXRulesModel : public QAbstractItemModel
{
    Q_OBJECT

    QList< Rule* > m_rulesList;
    RulesTreeItem* m_root;

    RulesTreeItem* itemFromIndex(const QModelIndex& index) const;

    void addFakeRule();
public:
    explicit YAXRulesModel(QObject *parent = 0);
    ~YAXRulesModel();

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
//    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
//    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    RulesTreeItem* root() const
    {   return m_root;  }
    void setRoot(RulesTreeItem* root);

    void needsReset()
    {   reset();    }

    void addRule(Rule* rule, int index = -1);

signals:

public slots:

};

#endif // YAXRULESMODEL_HPP
