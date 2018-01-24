#include "wireframemeshinstancedata.h"
#include "../../worldinfo.h"

WireframeMeshInstanceData::WireframeMeshInstanceData(QWidget *parent): NodeData(parent), data(nullptr)
{
    visualPrepare("wireframemeshinstance");
    prepareParamPanel();

    setDebugValue("Null");
}

WireframeMeshInstanceData::~WireframeMeshInstanceData()
{
    if(data)
        delete data;
}

bool WireframeMeshInstanceData::isPresent() const
{
    return data != nullptr;
}

const void *WireframeMeshInstanceData::getData()
{
    return (const void *)data;
}

void WireframeMeshInstanceData::setData(const void *newData)
{
    if(!newData)
    {
        delete data;
        setDebugValue("Null");

        return;
    }

    data = (WireframeMeshInstance *)newData;
    setDebugValue("Mesh instance is set");
}

const char *WireframeMeshInstanceData::dataType() const
{
    return typeid(WireframeMeshInstance).name();
}

const char *WireframeMeshInstanceData::dataType_s()
{
    return typeid(WireframeMeshInstance).name();
}

void WireframeMeshInstanceData::resetMovable()
{
    WorldInfo::getInstance().removeObject(data);

    if(data)
        delete data;
    data = nullptr;
    setDebugValue("Null");
}

