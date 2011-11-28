#include "rulesdockwidget.hpp"

RulesWidget::RulesWidget(QWidget *parent)
    : QSplitter(parent)
{
    setOrientation(Qt::Vertical);

    QSplitter* topSplitter    = new QSplitter;
    QSplitter* bottomSplitter = new QSplitter;

    m_rulesView       = new QTreeView;
    m_premisesView    = new QListView;
    m_conclusionsView = new QListView;

    m_btnRuleAdd          = new QPushButton(tr("Добавить"));
    m_btnRuleDelete       = new QPushButton(tr("Удалить"));
    m_btnRuleUp           = new QPushButton(tr("Выше"));
    m_btnRuleDown         = new QPushButton(tr("Ниже"));
    m_btnPremiseAdd       = new QPushButton(tr("Добавить"));
    m_btnPremiseDelete    = new QPushButton(tr("Удалить"));
    m_btnConclusionAdd    = new QPushButton(tr("Добавить"));
    m_btnConclusionDelete = new QPushButton(tr("Удалить"));

    topSplitter->addWidget(m_rulesView);

    QWidget* trWidget = new QWidget;
    QVBoxLayout* trl  = new QVBoxLayout;
    trWidget->setLayout(trl);
    trl->setSpacing(5);
    trl->addWidget(m_btnRuleAdd);
    trl->addWidget(m_btnRuleDelete);
    trl->addStretch();
    trl->addWidget(m_btnRuleUp);
    trl->addWidget(m_btnRuleDown);

    topSplitter->addWidget(trWidget);

    QGroupBox* blWidget = new QGroupBox(tr("Посылки"));
    QHBoxLayout* hbl    = new QHBoxLayout;
    blWidget->setLayout(hbl);
    hbl->addWidget(m_premisesView);

    QVBoxLayout* vbl = new QVBoxLayout;
    vbl->addWidget(m_btnPremiseAdd);
    vbl->addWidget(m_btnPremiseDelete);
    vbl->addStretch();

    hbl->addLayout(vbl);

    QGroupBox* brWidget = new QGroupBox(tr("Заключения"));
    QHBoxLayout* hbr    = new QHBoxLayout;
    brWidget->setLayout(hbr);
    hbr->addWidget(m_conclusionsView);

    QVBoxLayout* vbr = new QVBoxLayout;
    vbr->addWidget(m_btnConclusionAdd);
    vbr->addWidget(m_btnConclusionDelete);
    vbr->addStretch();

    hbr->addLayout(vbr);

    bottomSplitter->addWidget(blWidget);
    bottomSplitter->addWidget(brWidget);

    addWidget(topSplitter);
    addWidget(bottomSplitter);

    m_rulesView->setModel(YAXModels::instance()->rulesModel());
    m_rulesView->setItemDelegate(new RulesDelegate);
}

RulesDockWidget::RulesDockWidget(QString title) :
    QDockWidget(title)
{   setWidget(m_widget = new RulesWidget);  }
