#include "variablesdockwidget.hpp"

VariablesWidget::VariablesWidget(QWidget *parent) :
    QSplitter(parent)
{
    m_variablesList = new QListView;

    m_btnVariableAdd    = new QPushButton(tr("Добавить"));
    m_btnVariableChange = new QPushButton(tr("Изменить"));
    m_btnVariableDelete = new QPushButton(tr("Удалить"));

    m_btnVariableUp     = new QPushButton(tr("Выше"));
    m_btnVariableDown   = new QPushButton(tr("Ниже"));

    m_cbDerivable   = new QCheckBox(tr("Выводимая"));
    m_cbAskable     = new QCheckBox(tr("Запрашиваемая"));

    m_cbbDomain     = new QComboBox;

    m_pteQuestion   = new QPlainTextEdit;
    m_pteQuestion->setMinimumSize(100, 35);

    QWidget* rwidget = new QWidget;
    QVBoxLayout* rlayout = new QVBoxLayout;

    rwidget->setLayout(rlayout);

    rlayout->setSpacing(5);
    rlayout->addWidget(m_btnVariableAdd);
    rlayout->addWidget(m_btnVariableChange);
    rlayout->addWidget(m_btnVariableDelete);
    rlayout->addSpacing(10);
    rlayout->addWidget(m_btnVariableUp);
    rlayout->addWidget(m_btnVariableDown);

    QGroupBox* gbType = new QGroupBox(tr("Тип"));
    QVBoxLayout* ltype = new QVBoxLayout;
    gbType->setLayout(ltype);
    ltype->addWidget(m_cbDerivable);
    ltype->addWidget(m_cbAskable);

    rlayout->addWidget(gbType);

    QGroupBox* gbDomain = new QGroupBox(tr("Домен"));
    QVBoxLayout* lDomain = new QVBoxLayout;
    gbDomain->setLayout(lDomain);
    lDomain->addWidget(m_cbbDomain);

    rlayout->addWidget(gbDomain);

    QGroupBox* gbQuestion = new QGroupBox(tr("Вопрос"));
    QVBoxLayout* lquest = new QVBoxLayout;
    gbQuestion->setLayout(lquest);
    lquest->addWidget(m_pteQuestion);

    rlayout->addWidget(gbQuestion);

    addWidget(m_variablesList);
    addWidget(rwidget);

    m_cbbDomain->setEditable(true);
    m_cbbDomain->setModel(YAXModels::instance()->domainModel());
    m_variablesList->setModel(YAXModels::instance()->variablesModel());

    QObject::connect(m_btnVariableAdd, SIGNAL(clicked()),
                     SLOT(variableAdd()));
    QObject::connect(m_btnVariableChange, SIGNAL(clicked()),
                     SLOT(variableChange()));
    QObject::connect(m_btnVariableDelete, SIGNAL(clicked()),
                     SLOT(variableDelete()));

    QObject::connect(m_btnVariableUp, SIGNAL(clicked()),
                     SLOT(variableUp()));
    QObject::connect(m_btnVariableDown, SIGNAL(clicked()),
                     SLOT(variableDown()));

    QObject::connect(m_variablesList->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                     SLOT(variableSelectionChanged(QItemSelection,QItemSelection)));
}

void VariablesWidget::variableAdd()
{
    YAXVariablesModel* model = YAXModels::instance()->variablesModel();
    int count = model->rowCount();
    model->insertRow(count);
    m_variablesList->edit(model->index(count));
}

void VariablesWidget::variableChange()
{
    QItemSelectionModel* selected = m_variablesList->selectionModel();
    int count = selected->selectedRows().count();
    if (count == 1)
        m_variablesList->edit(selected->selectedRows().at(0));
}

void VariablesWidget::variableDelete()
{
    YAXVariablesModel* model = YAXModels::instance()->variablesModel();
    QItemSelectionModel* selected = m_variablesList->selectionModel();
    int count = selected->selectedRows().count();
    for (int i = 0; i < count; ++i)
        model->removeRow(selected->selectedRows().at(i).row(), QModelIndex());
}

void VariablesWidget::variableUp()
{
    YAXVariablesModel* model = YAXModels::instance()->variablesModel();
    QItemSelectionModel* selected = m_variablesList->selectionModel();
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

void VariablesWidget::variableDown()
{
    YAXVariablesModel* model = YAXModels::instance()->variablesModel();
    QItemSelectionModel* selected = m_variablesList->selectionModel();
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

void VariablesWidget::variableSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    YAXVariablesModel* model = YAXModels::instance()->variablesModel();
    if (deselected.count() == 1) {
        Variable* variable = model->variableList().at(deselected.indexes().at(0).row());
        QList<Domain*> domainsList = YAXModels::instance()->domainModel()->domainsList();
        Domain* domain = 0;
        int index = m_cbbDomain->currentIndex();
        if (index < domainsList.count() && index >= 0)
            domain = domainsList.at(index);
        variable->domain = domain;
        variable->derivable = m_cbDerivable->isChecked();
        variable->askable = m_cbAskable->isChecked();
        variable->question = m_pteQuestion->toPlainText();
    }

    if (selected.count() == 1) {
        Variable* variable = model->variableList().at(selected.indexes().at(0).row());
        m_cbDerivable->setChecked(variable->derivable);
        m_cbAskable->setChecked(variable->askable);
        m_pteQuestion->setPlainText(variable->question);
        m_cbbDomain->setCurrentIndex(YAXModels::instance()->domainModel()->domainsList().indexOf(variable->domain));
    }
}

VariablesDockWidget::VariablesDockWidget(QString title) :
    QDockWidget(title)
{    setWidget(m_widget = new VariablesWidget); }
