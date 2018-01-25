#include "objectsarray.h"
#include "../../sceneobject.h"

ObjectsArray::ObjectsArray(QWidget *parent): NodeData(parent), array(new QVector<SceneObject *>)
{
    visualPrepare("objectsarray");
    prepareParamPanel();
    setDebugValue("0");
}

bool ObjectsArray::isPresent() const
{
    return true;
}

const void *ObjectsArray::getData()
{
    return array;
}

void ObjectsArray::setData(const void *data)
{
    if(!data)
        delete array;

    array = (QVector<SceneObject *> *)data;
    setDebugValue(array ? QString::number(array->size()) : "0");
}

const char *ObjectsArray::dataType() const
{
    return typeid(QVector<SceneObject *> *).name();
}

const char *ObjectsArray::dataType_s()
{
    return typeid(QVector<SceneObject *> *).name();
}

void ObjectsArray::resetMovable()
{
    array->clear();
}
