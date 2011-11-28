#ifndef YAXDOMAINSMODEL_HPP
#define YAXDOMAINSMODEL_HPP

#include <QAbstractItemModel>
#include <QList>
#include <QItemSelection>
#include "./../YAXCore/yaxkb.hpp"

class YAXDomainsModel : public QAbstractItemModel
{
    Q_OBJECT

    bool checkDomainName(QString &domainName);

    QList< Domain* > m_domainsList;

public:
    explicit YAXDomainsModel(QObject *parent = 0);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    QList< Domain*> domainsList() const
    {   return m_domainsList;   }

    void setDomainsList(QList< Domain*> domainsList)
    {   m_domainsList = domainsList;    }

    void addDomain(Domain* domain)
    {    m_domainsList << domain;   }

    void needsReset()
    {   reset();    }

    void exchange(int row1, int row2);

signals:

public slots:
    void domainSelectionChanged(QItemSelection selected, QItemSelection deselected);

};

#endif // YAXDOMAINSMODEL_HPP
