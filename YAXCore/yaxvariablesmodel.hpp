#ifndef YAXVARIABLESMODEL_HPP
#define YAXVARIABLESMODEL_HPP

#include <QAbstractItemModel>
#include <QList>
#include "./../YAXCore/yaxkb.hpp"

class YAXVariablesModel : public QAbstractItemModel
{
    Q_OBJECT

    bool checkVariableName(QString& name);

    QList< Variable* > m_variablesList;

public:
    explicit YAXVariablesModel(QObject *parent = 0);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    QList< Variable* > variableList()
    {   return m_variablesList; }
    void setVariableList(QList< Variable* > list)
    {   m_variablesList = list; }

    void addVariable(Variable* variable)
    {   m_variablesList << variable;    }

    void needsReset()
    {   reset();    }

    void exchange(int row1, int row2);

signals:

public slots:

};

#endif // YAXVARIABLESMODEL_HPP
