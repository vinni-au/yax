#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow()
{   }

void MainWindow::fileCreate()
{

}

void MainWindow::fileOpen()
{
    QFileDialog fd;
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    fd.setNameFilter(tr("YAX expert systems (*.xml)"));
    if (fd.exec()) {
        YAXModels::instance()->fromXML(fd.selectedFiles().at(0));
    }
}

void MainWindow::fileSave()
{

}

void MainWindow::fileSaveAs()
{

}

void MainWindow::fileQuit()
{
    close();
}

void MainWindow::editDomains()
{

}

void MainWindow::editVariables()
{

}

void MainWindow::editRules()
{

}

void MainWindow::consultGoal()
{

}

void MainWindow::consultConsult()
{

}

void MainWindow::consultReasoning()
{

}

void MainWindow::helpAbout()
{

}

void MainWindow::helpAboutQt()
{    qApp->aboutQt();   }

void MainWindow::setupUI()
{
    m_domainsDock   = new DomainsDockWidget(tr("Домены"));
    m_variablesDock = new VariablesDockWidget(tr("Переменные"));
    m_rulesDock     = new RulesDockWidget(tr("Правила"));

    m_domainsDock->setVisible(false);
    m_variablesDock->setVisible(false);
    m_rulesDock->setVisible(true);

    addDockWidget(Qt::LeftDockWidgetArea, m_domainsDock);
    addDockWidget(Qt::LeftDockWidgetArea, m_variablesDock);
    addDockWidget(Qt::LeftDockWidgetArea, m_rulesDock);

    QMenuBar* mainMenu = menuBar();

    m_menuFile      = mainMenu->addMenu(tr("Файл"));
    m_menuEdit      = mainMenu->addMenu(tr("Редактировать"));
    m_menuConsult   = mainMenu->addMenu(tr("Консультация"));
    m_menuHelp      = mainMenu->addMenu(tr("Справка"));

    m_actFileCreate = m_menuFile->addAction(tr("Создать ЭС"),
                                            this, SLOT(fileCreate()));
    m_actFileOpen   = m_menuFile->addAction(tr("Открыть ЭС..."),
                                            this, SLOT(fileOpen()));
    m_actFileSave   = m_menuFile->addAction(tr("Сохранить ЭС..."),
                                            this, SLOT(fileSave()));
    m_actFileSaveAs = m_menuFile->addAction(tr("Сохранить ЭС как..."),
                                            this, SLOT(fileSaveAs()));
    m_menuFile->addSeparator();
    m_actFileQuit   = m_menuFile->addAction(tr("Выход"),
                                            this, SLOT(fileQuit()));

    m_actEditDomains    = m_menuEdit->addAction(tr("Домены..."),
                                                this, SLOT(editDomains()));
    m_actEditVariables  = m_menuEdit->addAction(tr("Переменные..."),
                                                this, SLOT(editVariables()));
    m_actEditRules      = m_menuEdit->addAction(tr("Правила..."),
                                                this, SLOT(editRules()));

    m_actConsultGoal        = m_menuConsult->addAction(tr("Задать цель консультации..."),
                                                       this, SLOT(consultGoal()));
    m_actConsultConsult     = m_menuConsult->addAction(tr("Начать консультацию..."),
                                                       this, SLOT(consultConsult()));
    m_actConsultReasoning   = m_menuConsult->addAction(tr("Объяснение..."),
                                                       this, SLOT(consultReasoning()));

    m_actHelpAbout      = m_menuHelp->addAction(tr("О программе..."),
                                                this, SLOT(helpAbout()));
    m_actHelpAboutQt    = m_menuHelp->addAction(tr("О Qt..."),
                                                this, SLOT(helpAboutQt()));
}

