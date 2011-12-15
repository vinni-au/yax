#ifndef DOMAINSDOCKWIDGET_HPP
#define DOMAINSDOCKWIDGET_HPP

#include <QDockWidget>
#include <QListView>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QFont>
#include <QGroupBox>
#include "YAXCore/yaxmodels.hpp"
#include "Commands.hpp"
#include "commandstack.hpp"

class DomainsWidget : public QSplitter
{
    Q_OBJECT

    QListView* m_domainsList;
    QListView* m_valuesList;

    QPushButton* m_btnDomainAdd;
    QPushButton* m_btnDomainChange;
    QPushButton* m_btnDomainDelete;

    QPushButton* m_btnDomainUp;
    QPushButton* m_btnDomainDown;

    QPushButton* m_btnValueAdd;
    QPushButton* m_btnValueChange;
    QPushButton* m_btnValueDelete;

    QPushButton* m_btnValueUp;
    QPushButton* m_btnValueDown;

public:
    explicit DomainsWidget(QWidget* parent = 0);

    void connectSlots();

protected slots:
    void domainAdd();
    void domainChange();
    void domainDelete();
    void domainUp();
    void domainDown();

    void valueAdd();
    void valueChange();
    void valueDelete();
    void valueUp();
    void valueDown();

    void updateValuesView();

public slots:

};

class DomainsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit DomainsDockWidget(QString title);

    void connectSlots();

protected:
    DomainsWidget* m_widget;
signals:

public slots:

};

#endif // DOMAINSDOCKWIDGET_HPP
