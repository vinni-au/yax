#ifndef YAXMODELS_HPP
#define YAXMODELS_HPP

#include <QObject>
#include <QHash>
#include <QtXml>
#include "yaxkb.hpp"
#include "yaxdomainsmodel.hpp"
#include "yaxvaluesmodel.hpp"
#include "yaxvariablesmodel.hpp"
#include "yaxrulesmodel.hpp"

class YAXModels : public QObject
{
    Q_OBJECT

    static YAXModels* m_instance;
    YAXModels();

    YAXDomainsModel* m_domainModel;
    YAXValuesModel* m_currentValuesModel;
    YAXVariablesModel* m_variablesModel;
    YAXRulesModel* m_rulesModel;

public:
    static YAXModels* instance();

    YAXDomainsModel* domainModel() const
    {   return m_domainModel;   }

    YAXValuesModel* currentValuesModel() const
    {   return m_currentValuesModel;    }

    YAXVariablesModel* variablesModel() const
    {   return m_variablesModel;    }

    YAXRulesModel* rulesModel() const
    {   return m_rulesModel;    }

    bool toXML(QString filename);
    bool fromXML(QString filename);

public slots:
};

#endif // YAXMODELS_HPP
