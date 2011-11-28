#include "yaxvariablesmodel.hpp"

YAXVariablesModel::YAXVariablesModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

int YAXVariablesModel::columnCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return 1;
    else return 0;
}

int YAXVariablesModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return m_variablesList.count();
    else return 0;
}

QModelIndex YAXVariablesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent == QModelIndex()) {
        if (row >= rowCount() || row < 0 || column < 0 || column > 1)
            return QModelIndex();
        else return createIndex(row, column, (void*)m_variablesList.at(row));
    } else return QModelIndex();
}

QModelIndex YAXVariablesModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant YAXVariablesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString value = m_variablesList.at(index.row())->name;
        return QVariant(value);
    } else return QVariant();
}

Qt::ItemFlags YAXVariablesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    return index.isValid() ? (result | Qt::ItemIsEditable) : result;
}

bool YAXVariablesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        QString svalue = value.value<QString>();
        if (!checkVariableName(svalue)) {
            removeRow(index.row());
        } else {
            m_variablesList.at(index.row())->name = svalue;
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool YAXVariablesModel::insertRow(int row, const QModelIndex &parent)
{
    if (row <= rowCount()) {
        beginInsertRows(parent, row, row);
        m_variablesList.insert(row, new Variable(""));
        endInsertRows();
        return true;
    } else return false;
}

bool YAXVariablesModel::removeRow(int row, const QModelIndex &parent)
{
    if (row >= 0 && row < rowCount()) {
        beginRemoveRows(parent, row, row);
        m_variablesList.removeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void YAXVariablesModel::exchange(int row1, int row2)
{
    QList<Variable*> list = variableList();
    int count = list.count();
    if (row1 >= 0 && row2 >=0 && row1 < count && row2 < count) {
        Variable* value1 = list.at(row1);
        Variable* value2 = list.at(row2);
        list[row1] = value2;
        list[row2] = value1;
    }
    setVariableList(list);
}

bool YAXVariablesModel::checkVariableName(QString &name)
{
    name = name.toUpper();
    name = name.simplified();
    if (!name.length())
        return false;
    return true;
}
