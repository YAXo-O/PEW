#include "appendmesh.h"
#include "../externalvariablefactory.h"
#include "../Data/wireframemeshinstancedata.h"
#include "../Data/objectsarray.h"

AppendMesh::AppendMesh(QString name, QWidget *parent): BaseNode(name, parent), fireCount(1), firedCount(0)
{
    mesh = ExternalVariableFactory::createExternal(WireframeMeshInstanceData::dataType_s(), "Mesh", DFF_READ);
    array = ExternalVariableFactory::createExternal(ObjectsArray::dataType_s(), "Array", DFF_BOTH);

    addDataPin(mesh->getPin());
    addDataPin(array->getPin());

    rearangePins();
}

AppendMesh::~AppendMesh()
{
    delete mesh;
    delete array;
}

void AppendMesh::enable(BaseNode *caller)
{
    if(fireCount && fireCount > firedCount || !fireCount)
    if((fireCount && fireCount > firedCount || !fireCount) && mesh->isDataPresent() && array->isConnected())
    {
        WireframeMeshInstance *meshData = (WireframeMeshInstance *)(mesh->getValue());
        QVector<SceneObject *> *vector = (QVector<SceneObject *> *)(array->getValue());

        if(vector != nullptr)
            vector->append(meshData);
        else
        {
            vector = new QVector<SceneObject *>;
            vector->append(meshData);
            array->setValue(vector);
        }
    }

    BaseNode::enable(caller);
}
