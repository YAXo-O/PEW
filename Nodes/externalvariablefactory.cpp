#include "externalvariablefactory.h"
#include "Data/booldata.h"

ExternalVariable *ExternalVariableFactory::createExternal(const char *varType, const QString &varName, const dataFlowFlag direction)
{
    ExternalVariable *res = nullptr;

    if(varType == BoolData::dataType_s())
        res = createBoolean(varName, direction);

    return res;
}

ExternalVariable *ExternalVariableFactory::createExternal(const char *varType, const QString &&varName, const dataFlowFlag direction)
{
    return createExternal(varType, varName, direction);
}

ExternalVariable *ExternalVariableFactory::createBoolean(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, BoolData::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}
