#include "externalvariablefactory.h"
#include "Data/alldata.h"

ExternalVariable *ExternalVariableFactory::createExternal(const char *varType, const QString &varName, const dataFlowFlag direction)
{
    ExternalVariable *res = nullptr;

    if(varType == BoolData::dataType_s())
        res = createBoolean(varName, direction);
    else if(varType == CameraData::dataType_s())
        res = createCamera(varName, direction);
    else if(varType == FloatData::dataType_s())
        res = createFloat(varName, direction);
    else if(varType == IntData::dataType_s())
        res = createInt(varName, direction);
    else if(varType == VectorData::dataType_s())
        res = createVector(varName, direction);
    else if(varType == LightData::dataType_s())
        res = createLight(varName, direction);
    else if(varType == SceneObjectData::dataType_s())
        res = createSceneObject(varName, direction);
    else if(varType == ColorData::dataType_s())
        res = createColor(varName, direction);
    else if(varType == WireframeMeshInstanceData::dataType_s())
        res = createWireframeMeshInstance(varName, direction);
    else if(varType == MaterialData::dataType_s())
        res = createMaterial(varName, direction);
    else if(varType == ObjectsArray::dataType_s())
        res = createObjectsArray(varName, direction);
    else if(varType == ParticleSystem::dataType_s())
        res = createParticleSystem(varName, direction);

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

ExternalVariable *ExternalVariableFactory::createFloat(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, FloatData::dataType_s(), direction);
    FloatDataParamsContainer *container = new FloatDataParamsContainer(new FloatDataWidget());
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createInt(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, IntData::dataType_s(), direction);
    IntDataParamsContainer *container = new IntDataParamsContainer(new IntDataWidget());
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createVector(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, VectorData::dataType_s(), direction);
    VectorParamsContainer *container = new VectorParamsContainer(new VectorDataWidget());
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createLight(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, LightData::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}

ExternalVariable *ExternalVariableFactory::createSceneObject(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, SceneObjectData::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}

ExternalVariable *ExternalVariableFactory::createColor(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, ColorData::dataType_s(), direction);
    ColorParamsContainer *container = new ColorParamsContainer(new ColorDataWidget());
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createWireframeMeshInstance(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, WireframeMeshInstanceData::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}

ExternalVariable *ExternalVariableFactory::createMaterial(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, MaterialData::dataType_s(), direction);
    MaterialParamsContainer *container = new MaterialParamsContainer(new MaterialDataWidget);
    ExternalVariable *res = new ExternalVariable(pin, container);

    return res;
}

ExternalVariable *ExternalVariableFactory::createObjectsArray(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, ObjectsArray::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}

ExternalVariable *ExternalVariableFactory::createParticleSystem(const QString &varName, const dataFlowFlag direction)
{
    DataPin *pin = new DataPin(varName, ParticleSystem::dataType_s(), direction);
    ExternalVariable *res = new ExternalVariable(pin, nullptr);

    return res;
}
