#include "yaxmodels.hpp"

YAXModels* YAXModels::m_instance = 0;

YAXModels::YAXModels() :
    QObject()
{
    m_domainModel           = new YAXDomainsModel;
    m_currentValuesModel    = new YAXValuesModel;
    m_variablesModel        = new YAXVariablesModel;
    m_rulesModel            = new YAXRulesModel;
}

YAXModels* YAXModels::instance()
{
    if (!m_instance)
        m_instance = new YAXModels;
    return m_instance;
}

bool YAXModels::toXML(QString filename)
{

    return false;
}

bool YAXModels::fromXML(QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QDomDocument doc;
        if (doc.setContent(&file)) {
            QDomElement root = doc.documentElement();
            if (root.tagName() == "yaxpertsystem" && root.childNodes().count() == 3) {
                QMap<QString, Domain*> domainsMap;
                QMap<QString, Value*> valuesMap;
                QMap<QString, Variable*> variablesMap;

                QDomElement domainsNode = root.childNodes().at(0).toElement();
                if (domainsNode.tagName() == "domains")
                    for (int i = 0; i < domainsNode.childNodes().count(); ++i) {
                        QDomElement domainElem = domainsNode.childNodes().at(i).toElement();
                        Domain* domain = new Domain(domainElem.attribute("name"));
                        for (int j = 0; j < domainElem.childNodes().count(); ++j) {
                            QDomElement valueElem = domainElem.childNodes().at(j).toElement();
                            Value* value = new Value(valueElem.attribute("name"), domain);
                            domain->values << value;
                            valuesMap[value->name] = value;
                        }
                        m_domainModel->addDomain(domain);
                        domainsMap[domain->name] = domain;
                    }
                m_domainModel->needsReset();
                m_currentValuesModel->needsReset();

                QDomElement variablesNode = root.childNodes().at(1).toElement();
                if (variablesNode.tagName() == "variables")
                    for (int i = 0; i < variablesNode.childNodes().count(); ++i) {
                        QDomElement variableElem = variablesNode.childNodes().at(i).toElement();
                        bool askable = QVariant(variableElem.attribute("askable")).toBool();
                        bool derivable = QVariant(variableElem.attribute("derivable")).toBool();
                        QString question = variableElem.attribute("question");
                        QString domainName = variableElem.attribute("domain");
                        Domain* domain = domainsMap[domainName];

                        Variable* variable = new Variable(variableElem.attribute("name"), domain,
                                                          derivable, askable, question);
                        m_variablesModel->addVariable(variable);
                        variablesMap[variable->name] = variable;
                    }
                m_variablesModel->needsReset();

                QDomElement rulesNode = root.childNodes().at(2).toElement();
                if (rulesNode.tagName() == "rules")
                    for (int i = 0; i < rulesNode.childNodes().count(); ++i) {
                        QDomElement ruleElement = rulesNode.childNodes().at(i).toElement();
                        Rule* rule = new Rule(ruleElement.attribute("name"), ruleElement.attribute("reasoning"));

                        if (ruleElement.childNodes().count() == 2) {
                            QDomElement premisesElem = ruleElement.childNodes().at(0).toElement();
                            for (int j = 0; j < premisesElem.childNodes().count(); ++j) {
                                QDomElement premiseElem = premisesElem.childNodes().at(j).toElement();
                                QString variableName = premiseElem.attribute("variable");
                                QString valueName = premiseElem.attribute("value");
                                Variable* variable = variablesMap[variableName];
                                Value* value = valuesMap[valueName];
                                Premise* premise = new Premise(variable, value);
                                rule->premises << premise;
                            }

                            QDomElement conclusionsElem = ruleElement.childNodes().at(1).toElement();
                            for (int j = 0; j < conclusionsElem.childNodes().count(); ++j) {
                                QDomElement conclusionElem = conclusionsElem.childNodes().at(j).toElement();
                                QString variableName = conclusionElem.attribute("variable");
                                QString valueName = conclusionElem.attribute("value");
                                Variable* variable = variablesMap[variableName];
                                Value* value = valuesMap[valueName];
                                Conclusion* conclusion = new Conclusion(variable, value);
                                rule->conclusions << conclusion;
                            }
                        }

                        m_rulesModel->addRule(rule);
                    }
                m_rulesModel->addFakeRule();
                m_rulesModel->needsReset();

            }
        }
        QMessageBox::about(0, "xml", doc.toString(4));
        file.close();
    }
    return true;
}
