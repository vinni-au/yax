#ifndef VARIABLESDOCKWIDGET_HPP
#define VARIABLESDOCKWIDGET_HPP

#include <QDockWidget>
#include <QListView>
#include <QSplitter>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QRegExp>
#include "YAXCore/yaxmodels.hpp"

class VariablesWidget : public QSplitter
{
    Q_OBJECT

    QListView* m_variablesList;

    QPushButton* m_btnVariableAdd;
    QPushButton* m_btnVariableChange;
    QPushButton* m_btnVariableDelete;

    QPushButton* m_btnVariableUp;
    QPushButton* m_btnVariableDown;

    QCheckBox* m_cbDerivable;
    QCheckBox* m_cbAskable;

    QComboBox* m_cbbDomain;

    QPlainTextEdit* m_pteQuestion;
public:
    explicit VariablesWidget(QWidget* parent = 0);

protected slots:
    void variableAdd();
    void variableChange();
    void variableDelete();

    void variableUp();
    void variableDown();

    void variableSelectionChanged(QItemSelection selected, QItemSelection deselected);
};

class VariablesDockWidget : public QDockWidget
{
    Q_OBJECT

    VariablesWidget* m_widget;

public:
    explicit VariablesDockWidget(QString title);
};

#endif // VARIABLESDOCKWIDGET_HPP
