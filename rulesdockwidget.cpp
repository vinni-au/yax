#include "rulesdockwidget.hpp"

RulesWidget::RulesWidget(QWidget *parent)
    : QSplitter(parent)
{
    setOrientation(Qt::Vertical);

    QSplitter* topSplitter    = new QSplitter;

    m_rulesView       = new QTreeView;

    m_btnRuleAdd          = new QPushButton(tr("Добавить"));
    m_btnRuleDelete       = new QPushButton(tr("Удалить"));
    m_btnRuleUp           = new QPushButton(tr("Выше"));
    m_btnRuleDown         = new QPushButton(tr("Ниже"));

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

    addWidget(topSplitter);

    m_rulesView->setModel(YAXModels::instance()->rulesModel());
    m_rulesView->setItemDelegate(new RulesDelegate);
}

RulesDockWidget::RulesDockWidget(QString title) :
    QDockWidget(title)
{   setWidget(m_widget = new RulesWidget);  }
