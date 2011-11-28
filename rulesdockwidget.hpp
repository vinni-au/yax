#ifndef RULESDOCKWIDGET_HPP
#define RULESDOCKWIDGET_HPP

#include <QDockWidget>
#include <QPushButton>
#include <QListView>
#include <QTreeView>
#include <QSplitter>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include "YAXCore/yaxmodels.hpp"
#include "YAXCore/rulesdelegate.hpp"

class RulesWidget : public QSplitter
{
    Q_OBJECT

    QTreeView* m_rulesView;

    QPushButton* m_btnRuleAdd;
    QPushButton* m_btnRuleDelete;

    QPushButton* m_btnRuleUp;
    QPushButton* m_btnRuleDown;

    QListView* m_premisesView;

    QPushButton* m_btnPremiseAdd;
    QPushButton* m_btnPremiseDelete;

    QListView* m_conclusionsView;

    QPushButton* m_btnConclusionAdd;
    QPushButton* m_btnConclusionDelete;

public:
    explicit RulesWidget(QWidget* parent = 0);
};

class RulesDockWidget : public QDockWidget
{
    Q_OBJECT

    RulesWidget* m_widget;
public:
    explicit RulesDockWidget(QString title);

};

#endif // RULESDOCKWIDGET_HPP
