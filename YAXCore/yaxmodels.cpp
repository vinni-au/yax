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
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.close();
    }
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

                QDomElement domainsNode = root.childNodes().at(0).toElement();
                if (domainsNode.tagName() == "domains")
                    for (int i = 0; i < domainsNode.childNodes().count(); ++i) {
                        QDomElement domainElem = domainsNode.childNodes().at(i).toElement();
                        Domain* domain = new Domain(domainElem.attribute("name"));
                        for (int j = 0; j < domainElem.childNodes().count(); ++j) {
                            QDomElement valueElem = domainElem.childNodes().at(j).toElement();
                            Value* value = new Value(valueElem.attribute("name"), domain);
                            domain->values << value;
                        }
                        m_domainModel->addDomain(domain);
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

                        QList<Domain*> dlist = m_domainModel->domainsList();

                        Variable* variable = new Variable(variableElem.attribute("name"));
                    }
                m_variablesModel->needsReset();

                QDomElement rulesNode = root.childNodes().at(2).toElement();
                if (rulesNode.tagName() == "rules" && rulesNode.childNodes().count() == 2)
                    for (int i = 0; i < rulesNode.childNodes().count(); ++i) {
                        QDomElement ruleElement = rulesNode.childNodes().at(i).toElement();
                        if (ruleElement.childNodes().count() == 2) {
                            QDomElement premisesElem = ruleElement.childNodes().at(0).toElement();
                            for (int i = 0; i < premisesElem.childNodes().count(); ++i) {

                            }

                            QDomElement conclusionsElem = ruleElement.childNodes().at(1).toElement();
                            for (int i = 0; i < conclusionsElem.childNodes().count(); ++i) {

                            }
                        }
                    }
                m_rulesModel->needsReset();

            }
        }

        file.close();
    }
    return true;
}
