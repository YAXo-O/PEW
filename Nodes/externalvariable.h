#ifndef EXTERNALVARIABLE_H
#define EXTERNALVARIABLE_H

#include "datapin.h"
#include "nodeparamscontainer.h"

class ExternalVariable
{
public:
    ExternalVariable(DataPin *pin, NodeParamsContainer *variablePanel);
    ~ExternalVariable();

    const void *getValue();
    void setValue(void *value);
    const char *getType();

    DataPin *getPin();
    const QString &getVarName();

    bool isConnected() const;
    bool isDataPresent() const;

    NodeParamsContainer *getParamsContainer() const;

private:
    DataPin *pin;
    NodeParamsContainer *variablePanel;
};

#endif // EXTERNALVARIABLE_H
