#include "lightdata.h"
#include "../../worldinfo.h"

LightData::LightData(QWidget *parent): NodeData(parent), data(nullptr)
{
    visualPrepare("light");
    prepareParamPanel();

    setDebugValue("Null");
}

LightData::~LightData()
{
    if(data)
        delete data;
}

bool LightData::isPresent() const
{
    if(data)
        return true;

    return false;
}

const void *LightData::getData()
{
    return (void *)data;
}

void LightData::setData(const void *newData)
{
    if(!newData)
    {
        delete data;
        setDebugValue("Null");

        return;
    }

    data = (BaseLight *)(newData);
    setDebugValue("Light is set");
}

const char *LightData::dataType() const
{
    return typeid(BaseLight).name();
}

const char *LightData::dataType_s()
{
    return typeid(BaseLight).name();
}

void LightData::resetMovable()
{
    WorldInfo::getInstance().removeObject(data);

    if(data)
        delete data;
    data = nullptr;
    setDebugValue("Null");
}
