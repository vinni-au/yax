#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QtGui>
#include <QAction>
#include "domainsdockwidget.hpp"
#include "variablesdockwidget.hpp"
#include "rulesdockwidget.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT    

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QMenu* m_menuFile;
    QMenu* m_menuEdit;
    QMenu* m_menuConsult;
    QMenu* m_menuHelp;

    QAction* m_actFileCreate;
    QAction* m_actFileOpen;
    QAction* m_actFileSave;
    QAction* m_actFileSaveAs;
    QAction* m_actFileQuit;

    QAction* m_actEditDomains;
    QAction* m_actEditVariables;
    QAction* m_actEditRules;

    QAction* m_actConsultGoal;
    QAction* m_actConsultConsult;
    QAction* m_actConsultReasoning;

    QAction* m_actHelpAbout;
    QAction* m_actHelpAboutQt;

    DomainsDockWidget* m_domainsDock;
    VariablesDockWidget* m_variablesDock;
    RulesDockWidget* m_rulesDock;

protected slots:
    void fileCreate();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void fileQuit();

    void editDomains();
    void editVariables();
    void editRules();

    void consultGoal();
    void consultConsult();
    void consultReasoning();

    void helpAbout();
    void helpAboutQt();

private:
    void setupUI();
};

#endif // MAINWINDOW_HPP
