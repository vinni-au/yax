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

QString YAXModels::toXML(int indent)
{
    QDomDocument doc;
    QDomElement root        = doc.createElement("yaxspertsystem");
    QDomElement domains     = doc.createElement("domains");
    QDomElement variables   = doc.createElement("variables");
    QDomElement rules       = doc.createElement("rules");

    doc.appendChild(root);
    root.appendChild(domains);
    root.appendChild(variables);
    root.appendChild(rules);

    QList<Domain*> domainslist = m_domainModel->domainsList();
    for (int i = 0; i < domainslist.count(); ++i) {
        Domain* d = domainslist.at(i);
        QDomElement domain = doc.createElement("domain");
        domain.setAttribute("name", d->name);
        for (int j = 0; j < d->values.count(); ++j) {
            QDomElement value = doc.createElement("value");
            value.setAttribute("name", d->values.at(j)->name);
            domain.appendChild(value);
        }
        domains.appendChild(domain);
    }

    QList<Variable*> variableslist = m_variablesModel->variableList();
    for (int i = 0; i < variableslist.count(); ++i) {
        Variable* v = variableslist.at(i);
        QDomElement variable = doc.createElement("variable");
        variable.setAttribute("name", v->name);
        variable.setAttribute("askable", v->askable ? "true" : "false");
        variable.setAttribute("derivable", v->derivable ? "true" : "false");
        variable.setAttribute("domain", v->domain->name);
        variable.setAttribute("question", v->question);
        variables.appendChild(variable);
    }

    QList<Rule*> ruleslist = m_rulesModel->rulesList();
    for (int i = 0; i < ruleslist.count(); ++i) {
        Rule* r = ruleslist.at(i);
        QDomElement rule = doc.createElement("rule");
        rule.setAttribute("name", r->name);
        rule.setAttribute("reasoning", r->reasoning);
        QDomElement premises = doc.createElement("premises");
        QDomElement conclusions = doc.createElement("conclusions");
        for (int j = 0; j < r->premises.count(); ++j) {
            QDomElement premise = doc.createElement("premise");
            premise.setAttribute("variable", r->premises.at(j)->variable->name);
            premise.setAttribute("value", r->premises.at(j)->value->name);
            premises.appendChild(premise);
        }
        for (int j = 0; j < r->conclusions.count(); ++j) {
            QDomElement premise = doc.createElement("conclusion");
            premise.setAttribute("variable", r->conclusions.at(j)->variable->name);
            premise.setAttribute("value", r->conclusions.at(j)->value->name);
            conclusions.appendChild(premise);
        }
        rule.appendChild(premises);
        rule.appendChild(conclusions);
        rules.appendChild(rule);
    }

    QMessageBox::about(0, "", doc.toString(4));

    return doc.toString(indent);
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
        file.close();
    }
    return true;
}
