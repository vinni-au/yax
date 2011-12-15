#include "yaxvaluesmodel.hpp"

YAXValuesModel::YAXValuesModel(QObject *parent) :
    QAbstractItemModel(parent)
{   }

int YAXValuesModel::columnCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return 1;
    else return 0;
}

int YAXValuesModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return m_valuesList.count();
    else return 0;
}

QModelIndex YAXValuesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        if (row >= rowCount() || row < 0 || column < 0 || column > 1)
            return QModelIndex();
        else return createIndex(row, column, (void*)m_valuesList.at(row));
    else return QModelIndex();
}

QModelIndex YAXValuesModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant YAXValuesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
        QString value = m_valuesList.at(index.row())->name;
        return QVariant(value);
    } else return QVariant();
}

Qt::ItemFlags YAXValuesModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    return index.isValid() ? (result | Qt::ItemIsEditable) : result;
}

bool YAXValuesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        QString svalue = value.value<QString>();
        if (!checkValueName(svalue)) {
            removeRow(index.row());
        } else {
            m_valuesList.at(index.row())->name = svalue;
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool YAXValuesModel::insertRow(int row, const QModelIndex &parent)
{
    if (row <= rowCount()) {
        beginInsertRows(parent, row, row);
        m_valuesList.insert(row, new Value());
        endInsertRows();
        return true;
    } else return false;
}

bool YAXValuesModel::removeRow(int row, const QModelIndex &parent)
{
    if (row >= 0 && row < rowCount()) {
        beginRemoveRows(parent, row, row);
        m_valuesList.removeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void YAXValuesModel::exchange(int row1, int row2)
{
    QList<Value*> list = valuesList();
    int count = list.count();
    if (row1 >= 0 && row2 >=0 && row1 < count && row2 < count) {
        Value* value1 = list.at(row1);
        Value* value2 = list.at(row2);
        list[row1] = value2;
        list[row2] = value1;
    }
    setValuesList(list);
}

bool YAXValuesModel::checkValueName(QString &valueName)
{
    valueName = valueName.toUpper();
    valueName = valueName.simplified();
    if (!valueName.length())
        return false;
    return true;
}

void YAXValuesModel::setValuesList(QList<Value *> list)
{
    m_valuesList = list;
    emit dataChanged(createIndex(0, 0), createIndex(list.count(), 0));
}
