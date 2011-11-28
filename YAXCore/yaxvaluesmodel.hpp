#ifndef YAXVALUESMODEL_HPP
#define YAXVALUESMODEL_HPP

#include <QAbstractItemModel>
#include <QList>
#include "./../YAXCore/yaxkb.hpp"

class YAXValuesModel : public QAbstractItemModel
{
    Q_OBJECT

    bool checkValueName(QString &valueName);

    QList< Value* > m_valuesList;

public:
    explicit YAXValuesModel(QObject *parent = 0);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    QList< Value* > valuesList() const
    {   return m_valuesList;    }    
    void setValuesList(QList< Value* > list);

    void addValue(Value* value)
    {   m_valuesList << value;  }

    void needsReset()
    {   reset();    }

    void exchange(int row1, int row2);

signals:
    void viewUpdateNeeded();
};

#endif // YAXVALUESMODEL_HPP
