#include "externalvariablefactory.h"
#include "Data/alldata.h"

ExternalVariable *ExternalVariableFactory::createExternal(const char *varType, const QString &varName, const dataFlowFlag direction)
{
    ExternalVariable *res = nullptr;

    if(varType == BoolData::dataType_s())
        res = createBoolean(varName, direction);
    else if(varType == CameraData::dataType_s())
        res = createCamera(varName, direction);

    return res;
}

ExternalVariable *ExternalVariableFactory::createExternal(const char *varType, const QString &&varName, const dataFlowFlag direction)
{
    return createExternal(varType, varName, direction);
}

ExternalVariable *ExternalVariableFactory::createBoolean(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, BoolData::dataType_s(), direction);
    BoolDataWidget *wid = new BoolDataWidget();
    wid->setText(varName);
    BoolParamsContainer *container = new BoolParamsContainer(wid);
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createCamera(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, CameraData::dataType_s(), direction);
    CameraParamsContainer *container = new CameraParamsContainer(new CameraDataWidget());
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}
