#include "cameradata.h"

#include <QDebug>

CameraData::CameraData(QWidget *parent): NodeData(parent), data(nullptr)
{
    visualPrepare(getKeyName());
    prepareParamPanel();
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
        delete data;

    data = (Camera *)(newData);
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
    if(data)
        delete data;
    data = nullptr;
}

void CameraData::paintEvent(QPaintEvent *pe)
{
    NodeData::paintEvent(pe);

    if(data)
        setDebugValue("Camera is set: ");
    else
        setDebugValue("Null");
}

void CameraData::prepareParamPanel()
{
    NodeData::prepareParamPanel();
}
