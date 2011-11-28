#include "yaxdomainsmodel.hpp"

YAXDomainsModel::YAXDomainsModel(QObject *parent) :
    QAbstractItemModel(parent)
{   }

int YAXDomainsModel::columnCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return 1;
    else return 0;
}

int YAXDomainsModel::rowCount(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return m_domainsList.count();
    else return 0;
}

QModelIndex YAXDomainsModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        if (row >= rowCount() || row < 0 || column < 0 || column > 1)
            return QModelIndex();
        else return createIndex(row, column, (void*)m_domainsList.at(row));
    else return QModelIndex();
}

QModelIndex YAXDomainsModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

QVariant YAXDomainsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    else if (role == Qt::DisplayRole || role == Qt::EditRole) {
            QString domain = m_domainsList.at(index.row())->name;
            return QVariant(domain);
        } else return QVariant();
}

Qt::ItemFlags YAXDomainsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    return index.isValid() ? (result | Qt::ItemIsEditable) : result;
}

bool YAXDomainsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        QString svalue = value.value<QString>();
        if (!checkDomainName(svalue)) {
            removeRow(index.row());
        } else {
            m_domainsList.at(index.row())->name = svalue;
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

bool YAXDomainsModel::insertRow(int row, const QModelIndex &parent)
{
    if (row <= rowCount()) {
        beginInsertRows(parent, row, row);
        m_domainsList.insert(row, new Domain());
        endInsertRows();
        return true;
    } else return false;
}

bool YAXDomainsModel::removeRow(int row, const QModelIndex &parent)
{
    if (row >= 0 && row < rowCount()) {
        beginRemoveRows(parent, row, row);
        m_domainsList.removeAt(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void YAXDomainsModel::exchange(int row1, int row2)
{
    QList<Domain*> list = domainsList();
    int count = list.count();
    if (row1 >= 0 && row2 >=0 && row1 < count && row2 < count) {
        Domain* value1 = list.at(row1);
        Domain* value2 = list.at(row2);
        list[row1] = value2;
        list[row2] = value1;
    }
    setDomainsList(list);
}

bool YAXDomainsModel::checkDomainName(QString &domainName)
{
    domainName = domainName.toUpper();
    domainName = domainName.simplified();
    if (!domainName.length())
        return false;
    return true;
}

#include "./../YAXCore/yaxmodels.hpp"

void YAXDomainsModel::domainSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    if (deselected.count() == 1) {
        Domain* domain = YAXModels::instance()->domainModel()->domainsList().at(deselected.at(0).indexes().at(0).row());
        QList<Value*> values = YAXModels::instance()->currentValuesModel()->valuesList();
        domain->values = values;
    }

    if (selected.count() == 1) {
        Domain* domain = YAXModels::instance()->domainModel()->domainsList().at(selected.at(0).indexes().at(0).row());
        YAXModels::instance()->currentValuesModel()->setValuesList(domain->values);
    }
}
