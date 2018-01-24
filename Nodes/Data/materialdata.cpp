#include "materialdata.h"

MaterialData::MaterialData(QWidget *parent): NodeData(parent)
{
    visualPrepare("material");
    prepareParamPanel();
    setDebugValue("Null");
}

MaterialData::~MaterialData()
{
    if(data)
        delete data;
}

bool MaterialData::isPresent() const
{
    return data != nullptr;
}

const void *MaterialData::getData()
{
    return (void *)data;
}

void MaterialData::setData(const void *newData)
{
    if(!newData)
    {
        delete data;
        setDebugValue("Null");

        return;
    }

    data = (Material *)newData;
    setDebugValue("Material is set");
}

const char *MaterialData::dataType() const
{
    return typeid(Material).name();
}

const char *MaterialData::dataType_s()
{
    return typeid(Material).name();
}

void MaterialData::resetMovable()
{
    if(data)
        delete data;

    data = nullptr;
    setDebugValue("Null");
}
