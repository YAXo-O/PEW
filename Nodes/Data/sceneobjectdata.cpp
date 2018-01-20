#include "sceneobjectdata.h"

SceneObjectData::SceneObjectData(QWidget *parent): NodeData(parent), data(nullptr)
{
    visualPrepare("scene_object");
}

SceneObjectData::~SceneObjectData()
{
    if(data)
        delete data;
}

bool SceneObjectData::isPresent() const
{
    return data != nullptr;
}

const void *SceneObjectData::getData()
{
    return data;
}

void SceneObjectData::setData(const void *newData)
{
    if(data)
        delete data;

    void *_data = const_cast<void *>(newData);
    data = reinterpret_cast<SceneObject *>(_data);
    if(!data)
    {
        data = nullptr;
        throw std::bad_cast();
    }
}

const char *SceneObjectData::dataType() const
{
    return typeid(SceneObject).name();
}

const char *SceneObjectData::dataType_s()
{
    return typeid(SceneObject).name();
}
