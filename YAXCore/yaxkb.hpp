#ifndef YAXKB_HPP
#define YAXKB_HPP

#include <QList>
#include <QString>

struct Value
{
    QString name;
    struct Domain* domain;

    Value(QString name_ = QString(), struct Domain* domain_ = 0) :
        name(name_), domain(domain_)
    {   }
};

struct Domain
{
    QString name;
    QList< Value* >  values;

    Domain(QString name_ = QString(), QList<Value*> values_ = QList<Value*>())
        : name(name_), values(values_)
    {   }
};

struct Variable
{
    QString name;
    Domain* domain;
    bool derivable;
    bool askable;
    QString question;

    Variable(QString name, Domain* domain_ = 0, bool derivable_ = false, bool askable_ = true, QString question_ = QString())
        : name(name), domain(domain_), derivable(derivable_), askable(askable_), question(question_)
    {   }
};

struct Premise
{
    Variable* variable;
    Value* value;

    Premise(Variable* variable_ = 0, Value* value_ = 0)
        : variable(variable_), value(value_)
    {   }
};

struct Conclusion
{
    Variable* variable;
    Value* value;

    Conclusion(Variable* variable_ = 0, Value* value_ = 0)
        : variable(variable_), value(value_)
    {   }
};

struct Rule
{
    QString name;
    QString reasoning;
    QList< Premise* > premises;
    QList< Conclusion* > conclusions;
    bool worked;

    Rule(QString name_ = QString(), QString reasoning_ = QString(),
         QList<Premise*> premises_ = QList<Premise*>(),  QList<Conclusion*> conclusions_ = QList<Conclusion*>())
        : name(name_), reasoning(reasoning_), premises(premises_), conclusions(conclusions_), worked(false)
    {   }
};

#endif // YAXKB_HPP
