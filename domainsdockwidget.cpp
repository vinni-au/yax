#include "domainsdockwidget.hpp"

DomainsWidget::DomainsWidget(QWidget *parent) :
    QSplitter(parent)
{
    m_domainsList = new QListView;
    m_valuesList = new QListView;

    QGroupBox* lwidget = new QGroupBox(tr("Домены"));
    QGroupBox* rwidget = new QGroupBox(tr("Значения"));

    QVBoxLayout* lvlayout = new QVBoxLayout;
    QHBoxLayout* lhlayout = new QHBoxLayout;

    m_btnDomainAdd = new QPushButton(tr("Добавить"));
    m_btnDomainChange = new QPushButton(tr("Изменить"));
    m_btnDomainDelete = new QPushButton(tr("Удалить"));

    m_btnDomainUp = new QPushButton(tr("Выше"));
    m_btnDomainDown = new QPushButton(tr("Ниже"));

    lvlayout->setSpacing(5);
    lvlayout->addWidget(m_btnDomainAdd);
    lvlayout->addWidget(m_btnDomainChange);
    lvlayout->addWidget(m_btnDomainDelete);
    lvlayout->addStretch();
    lvlayout->addWidget(m_btnDomainUp);
    lvlayout->addWidget(m_btnDomainDown);

    lhlayout->addWidget(m_domainsList);
    lhlayout->addLayout(lvlayout);

    lwidget->setLayout(lhlayout);

    QVBoxLayout* rvlayout = new QVBoxLayout;
    QHBoxLayout* rhlayout = new QHBoxLayout;

    m_btnValueAdd = new QPushButton(tr("Добавить"));
    m_btnValueChange = new QPushButton(tr("Изменить"));
    m_btnValueDelete = new QPushButton(tr("Удалить"));

    m_btnValueUp = new QPushButton(tr("Выше"));
    m_btnValueDown = new QPushButton(tr("Ниже"));

    rvlayout->setSpacing(5);
    rvlayout->addWidget(m_btnValueAdd);
    rvlayout->addWidget(m_btnValueChange);
    rvlayout->addWidget(m_btnValueDelete);
    rvlayout->addStretch();
    rvlayout->addWidget(m_btnValueUp);
    rvlayout->addWidget(m_btnValueDown);

    rhlayout->addWidget(m_valuesList);
    rhlayout->addLayout(rvlayout);

    rwidget->setLayout(rhlayout);

    addWidget(lwidget);
    addWidget(rwidget);

    m_domainsList->setModel(YAXModels::instance()->domainModel());
    m_valuesList->setModel(YAXModels::instance()->currentValuesModel());

    QObject::connect(m_btnDomainAdd, SIGNAL(clicked()),
                     SLOT(domainAdd()));
    QObject::connect(m_btnDomainChange, SIGNAL(clicked()),
                     SLOT(domainChange()));
    QObject::connect(m_btnDomainDelete, SIGNAL(clicked()),
                     SLOT(domainDelete()));
    QObject::connect(m_btnDomainUp, SIGNAL(clicked()),
                     SLOT(domainUp()));
    QObject::connect(m_btnDomainDown, SIGNAL(clicked()),
                     SLOT(domainDown()));

    QObject::connect(m_btnValueAdd, SIGNAL(clicked()),
                     SLOT(valueAdd()));
    QObject::connect(m_btnValueChange, SIGNAL(clicked()),
                     SLOT(valueChange()));
    QObject::connect(m_btnValueDelete, SIGNAL(clicked()),
                     SLOT(valueDelete()));
    QObject::connect(m_btnValueUp, SIGNAL(clicked()),
                     SLOT(valueUp()));
    QObject::connect(m_btnValueDown, SIGNAL(clicked()),
                     SLOT(valueDown()));

    QObject::connect(m_domainsList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     YAXModels::instance()->domainModel(), SLOT(domainSelectionChanged(QItemSelection,QItemSelection)));
    QObject::connect(YAXModels::instance()->currentValuesModel(), SIGNAL(viewUpdateNeeded()),
                     SLOT(updateValuesView()));
}

void DomainsWidget::domainAdd()
{
    YAXDomainsModel* model = YAXModels::instance()->domainModel();
    int count = model->rowCount();
    model->insertRow(count);
    m_domainsList->edit(model->index(count));
}

void DomainsWidget::domainChange()
{
    QItemSelectionModel* selected = m_domainsList->selectionModel();
    int count = selected->selectedRows().count();
    if (count == 1)
        m_domainsList->edit(selected->selectedRows().at(0));
}

void DomainsWidget::domainDelete()
{
    YAXDomainsModel* model = YAXModels::instance()->domainModel();
    QItemSelectionModel* selected = m_domainsList->selectionModel();
    int count = selected->selectedRows().count();
    for (int i = 0; i < count; ++i)
        model->removeRow(selected->selectedRows().at(i).row(), QModelIndex());
}

void DomainsWidget::domainUp()
{
    YAXDomainsModel* model = YAXModels::instance()->domainModel();
    QItemSelectionModel* selected = m_domainsList->selectionModel();
    int count = model->rowCount();
    if (selected->selectedRows().count()) {
        int row = selected->selectedRows().at(0).row();
        model->exchange(row, row - 1);
        selected->clear();
        int rows = 0;
        if (row - 1 < count && row - 1 >= 0)
            rows = row - 1;
        else rows = row;
        selected->select(model->index(rows), QItemSelectionModel::Select);
    }
}

void DomainsWidget::domainDown()
{
    YAXDomainsModel* model = YAXModels::instance()->domainModel();
    QItemSelectionModel* selected = m_domainsList->selectionModel();
    int count = model->rowCount();
    if (selected->selectedRows().count()) {
        int row = selected->selectedRows().at(0).row();
        model->exchange(row, row + 1);
        selected->clear();
        int rows = 0;
        if (row + 1 < count && row + 1 >= 0)
            rows = row + 1;
        else rows = row;
        selected->select(model->index(rows), QItemSelectionModel::Select);
    }
}

void DomainsWidget::valueAdd()
{
    YAXValuesModel* model = YAXModels::instance()->currentValuesModel();
    int count = model->rowCount();
    model->insertRow(count);
    m_valuesList->edit(model->index(count));
}

void DomainsWidget::valueChange()
{
    QItemSelectionModel* selected = m_valuesList->selectionModel();
    int count = selected->selectedRows().count();
    if (count == 1)
        m_valuesList->edit(selected->selectedRows().at(0));
}

void DomainsWidget::valueDelete()
{
    YAXValuesModel* model = YAXModels::instance()->currentValuesModel();
    QItemSelectionModel* selected = m_valuesList->selectionModel();
    int count = selected->selectedRows().count();
    for (int i = 0; i < count; ++i)
        model->removeRow(selected->selectedRows().at(i).row(), QModelIndex());
}

void DomainsWidget::valueUp()
{
    YAXValuesModel* model = YAXModels::instance()->currentValuesModel();
    QItemSelectionModel* selected = m_valuesList->selectionModel();
    int count = model->rowCount();
    if (selected->selectedRows().count()) {
        int row = selected->selectedRows().at(0).row();
        model->exchange(row, row - 1);
        selected->clear();
        int rows = 0;
        if (row - 1 < count && row - 1 >= 0)
            rows = row - 1;
        else rows = row;
        selected->select(model->index(rows), QItemSelectionModel::Select);
    }
}

void DomainsWidget::valueDown()
{
    YAXValuesModel* model = YAXModels::instance()->currentValuesModel();
    QItemSelectionModel* selected = m_valuesList->selectionModel();
    int count = model->rowCount();
    if (selected->selectedRows().count()) {
        int row = selected->selectedRows().at(0).row();
        model->exchange(row, row + 1);
        selected->clear();
        int rows = 0;
        if (row + 1 < count && row + 1 >= 0)
            rows = row + 1;
        else rows = row;
        selected->select(model->index(rows), QItemSelectionModel::Select);
    }
}

void DomainsWidget::updateValuesView()
{
    m_valuesList->setFocus();
    m_domainsList->setFocus();
}

DomainsDockWidget::DomainsDockWidget(QString title):
    QDockWidget(title)
{
    setWidget(m_widget = new DomainsWidget);
}
