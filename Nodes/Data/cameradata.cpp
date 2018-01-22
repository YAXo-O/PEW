#include "cameradata.h"
#include "../../worldinfo.h"

CameraData::CameraData(QWidget *parent): NodeData(parent), data(nullptr)
{
    visualPrepare("camera");
    prepareParamPanel();
    setDebugValue("Null");
}

CameraData::~CameraData()
{
    if(data)
        delete data;
}

bool CameraData::isPresent() const
{
    if(data)
        return true;

    return false;
}

const void *CameraData::getData()
{
    return (void *)data;
}

void CameraData::setData(const void *newData)
{
    if(!newData)
    {
        delete data;
        setDebugValue("Null");

        return;
    }

    data = (Camera *)(newData);
    setDebugValue("Camera is set");
}

const char *CameraData::dataType() const
{
    return typeid(Camera).name();
}

const char *CameraData::dataType_s()
{
    return typeid(Camera).name();
}

void CameraData::resetMovable()
{
    WorldInfo::getInstance().removeObject(data);
    if(data)
        delete data;

    data = nullptr;
    setDebugValue("Null");
}
