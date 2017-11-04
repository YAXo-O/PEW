#ifndef EXTERNALVARIABLE_H
#define EXTERNALVARIABLE_H

#include "datapin.h"

class ExternalVariable
{
public:
    ExternalVariable(DataPin *pin, QWidget *variablePanel);
    ~ExternalVariable();

    void *getValue();
    void setValue(void *value);
    const char *getType();

    DataPin *getPin();
    const QString &getVarName();

private:
    DataPin *pin;
    QWidget *variablePanel;
};

#endif // EXTERNALVARIABLE_H
