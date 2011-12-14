#-------------------------------------------------
#
# Project created by QtCreator 2011-09-15T20:12:31
#
#-------------------------------------------------

QT       += core gui xml

TARGET = yax
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    domainsdockwidget.cpp \
    YAXCore/yaxmodels.cpp \
    variablesdockwidget.cpp \
    rulesdockwidget.cpp \
    YAXCore/yaxvariablesmodel.cpp \
    YAXCore/yaxvaluesmodel.cpp \
    YAXCore/yaxdomainsmodel.cpp \
    YAXCore/yaxrulesmodel.cpp \
    YAXCore/rulestreeitem.cpp \
    YAXCore/rulesdelegate.cpp \
    Commands/domainaddcommand.cpp \
    Commands/domaindeletecommand.cpp \
    Commands/domainrenamecommand.cpp \
    Commands/domainmovecommand.cpp \
    Commands/valueaddcommand.cpp \
    Commands/valuedeletecommand.cpp \
    Commands/valuerenamecommand.cpp \
    Commands/valuemovecommand.cpp \
    Commands/variableaddcommand.cpp \
    Commands/variabledeletecommand.cpp \
    Commands/variablerenamecommand.cpp \
    Commands/variablechangecommand.cpp \
    Commands/variablemovecommand.cpp \
    Commands/ruleaddcommand.cpp \
    Commands/ruledeletecommand.cpp \
    Commands/rulerenamecommand.cpp \
    Commands/reasoningchangecommand.cpp \
    Commands/premiseaddcommand.cpp \
    Commands/premisedeletecommand.cpp \
    Commands/conclusionaddcommand.cpp \
    Commands/conclusiondeletecommand.cpp \
    Commands/premisechangecommand.cpp \
    Commands/conclusionchangecommand.cpp \
    Commands/rulemovecommand.cpp \
    Commands/premisemovecommand.cpp \
    Commands/conclusionmovecommand.cpp


HEADERS  += mainwindow.hpp \
    domainsdockwidget.hpp \
    YAXCore/yaxmodels.hpp \
    variablesdockwidget.hpp \
    rulesdockwidget.hpp \
    YAXCore/yaxkb.hpp \
    YAXCore/yaxvariablesmodel.hpp \
    YAXCore/yaxvaluesmodel.hpp \
    YAXCore/yaxdomainsmodel.hpp \
    YAXCore/yaxrulesmodel.hpp \
    YAXCore/rulestreeitem.hpp \
    YAXCore/rulesdelegate.hpp \
    Commands.hpp \
    Commands/domainaddcommand.hpp \
    Commands/domaindeletecommand.hpp \
    Commands/domainrenamecommand.hpp \
    Commands/domainmovecommand.hpp \
    Commands/valueaddcommand.hpp \
    Commands/valuedeletecommand.hpp \
    Commands/valuerenamecommand.hpp \
    Commands/valuemovecommand.hpp \
    Commands/variableaddcommand.hpp \
    Commands/variabledeletecommand.hpp \
    Commands/variablerenamecommand.hpp \
    Commands/variablechangecommand.hpp \
    Commands/variablemovecommand.hpp \
    Commands/ruleaddcommand.hpp \
    Commands/ruledeletecommand.hpp \
    Commands/rulerenamecommand.hpp \
    Commands/reasoningchangecommand.hpp \
    Commands/premiseaddcommand.hpp \
    Commands/premisedeletecommand.hpp \
    Commands/conclusionaddcommand.hpp \
    Commands/conclusiondeletecommand.hpp \
    Commands/premisechangecommand.hpp \
    Commands/conclusionchangecommand.hpp \
    Commands/rulemovecommand.hpp \
    Commands/premisemovecommand.hpp \
    Commands/conclusionmovecommand.hpp
