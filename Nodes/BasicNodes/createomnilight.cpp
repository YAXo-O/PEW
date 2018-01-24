#include "createomnilight.h"
#include "../Data/alldata.h"
#include "../externalvariablefactory.h"
#include "../../worldinfo.h"

CreateOmniLight::CreateOmniLight(QString nodeName, QWidget *parent): BaseNode(nodeName, parent)
{
    light = ExternalVariableFactory::createExternal(LightData::dataType_s(), "Light", DFF_WRITE);
    pos = ExternalVariableFactory::createExternal(VectorData::dataType_s(), "Position", DFF_READ);
    intensity = ExternalVariableFactory::createExternal(FloatData::dataType_s(), "Intensity", DFF_READ);
    color = ExternalVariableFactory::createExternal(ColorData::dataType_s(), "Color", DFF_READ);

    addDataPin(light->getPin());
    addDataPin(pos->getPin());
    addDataPin(intensity->getPin());
    addDataPin(color->getPin());

    appendExternalParamsWidget(pos->getParamsContainer()->getParamsPanel());
    appendExternalParamsWidget(intensity->getParamsContainer()->getParamsPanel());
    appendExternalParamsWidget(color->getParamsContainer()->getParamsPanel());

    rearangePins();
}

void CreateOmniLight::enable(BaseNode *caller)
{
    if(!light->isDataPresent() && light->isConnected())
    {
        lightInfo props;
        props.color = *((QColor *)color->getValue());
        props.intensity = *((double *)intensity->getValue());
        props.position = *((QVector3D *)pos->getValue());

        BaseLight *l = new BaseLight(props);
        light->setValue(l);
        WorldInfo::getInstance().registerObject(l);
    }

    BaseNode::enable(caller);
}
