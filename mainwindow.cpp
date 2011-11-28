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
    m_domainsDock   = new DomainsDockWidget(tr("������"));
    m_variablesDock = new VariablesDockWidget(tr("����������"));
    m_rulesDock     = new RulesDockWidget(tr("�������"));

    m_domainsDock->setVisible(false);
    m_variablesDock->setVisible(false);
    m_rulesDock->setVisible(true);

    addDockWidget(Qt::LeftDockWidgetArea, m_domainsDock);
    addDockWidget(Qt::LeftDockWidgetArea, m_variablesDock);
    addDockWidget(Qt::LeftDockWidgetArea, m_rulesDock);

    QMenuBar* mainMenu = menuBar();

    m_menuFile      = mainMenu->addMenu(tr("����"));
    m_menuEdit      = mainMenu->addMenu(tr("�������������"));
    m_menuConsult   = mainMenu->addMenu(tr("������������"));
    m_menuHelp      = mainMenu->addMenu(tr("�������"));

    m_actFileCreate = m_menuFile->addAction(tr("������� ��"),
                                            this, SLOT(fileCreate()));
    m_actFileOpen   = m_menuFile->addAction(tr("������� ��..."),
                                            this, SLOT(fileOpen()));
    m_actFileSave   = m_menuFile->addAction(tr("��������� ��..."),
                                            this, SLOT(fileSave()));
    m_actFileSaveAs = m_menuFile->addAction(tr("��������� �� ���..."),
                                            this, SLOT(fileSaveAs()));
    m_menuFile->addSeparator();
    m_actFileQuit   = m_menuFile->addAction(tr("�����"),
                                            this, SLOT(fileQuit()));

    m_actEditDomains    = m_menuEdit->addAction(tr("������..."),
                                                this, SLOT(editDomains()));
    m_actEditVariables  = m_menuEdit->addAction(tr("����������..."),
                                                this, SLOT(editVariables()));
    m_actEditRules      = m_menuEdit->addAction(tr("�������..."),
                                                this, SLOT(editRules()));

    m_actConsultGoal        = m_menuConsult->addAction(tr("������ ���� ������������..."),
                                                       this, SLOT(consultGoal()));
    m_actConsultConsult     = m_menuConsult->addAction(tr("������ ������������..."),
                                                       this, SLOT(consultConsult()));
    m_actConsultReasoning   = m_menuConsult->addAction(tr("����������..."),
                                                       this, SLOT(consultReasoning()));

    m_actHelpAbout      = m_menuHelp->addAction(tr("� ���������..."),
                                                this, SLOT(helpAbout()));
    m_actHelpAboutQt    = m_menuHelp->addAction(tr("� Qt..."),
                                                this, SLOT(helpAboutQt()));
}

