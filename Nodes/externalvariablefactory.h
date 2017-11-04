#ifndef EXTERNALVARIABLEFACTORY_H
#define EXTERNALVARIABLEFACTORY_H

#include "externalvariable.h"

class ExternalVariableFactory
{
public:
    static ExternalVariable *createExternal(const char *varType, const QString &varName, const dataFlowFlag direction);
    static ExternalVariable *createExternal(const char *varType, const QString &&varName, const dataFlowFlag direction);

private:
    static ExternalVariable *createBoolean(const QString &varName, const dataFlowFlag direction);
};

#endif // EXTERNALVARIABLEFACTORY_H
