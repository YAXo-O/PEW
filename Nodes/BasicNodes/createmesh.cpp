#include "createmesh.h"
#include "../externalvariablefactory.h"
#include "../Data/wireframemeshinstancedata.h"
#include "../../worldinfo.h"
#include "../NodesWidgets/createmeshwidget.h"

CreateMesh::CreateMesh(QString nodeName, QWidget *parent): BaseNode(nodeName, parent),
    wid(new CreateMeshParamsContainer(new CreateMeshWidget))
{
    mesh = ExternalVariableFactory::createExternal(WireframeMeshInstanceData::dataType_s(),
                                                   "WireframeMeshInstance", DFF_WRITE);
    addDataPin(mesh->getPin());

    rearangePins();

    appendParamsWidget(wid->getParamsPanel());
}

void CreateMesh::enable(BaseNode *caller)
{
    if(!mesh->isDataPresent() && mesh->isConnected())
    {
        WorldInfo &info = WorldInfo::getInstance();
        QString name = *((QString *)wid->getValue());
        WireframeMesh *m = info.meshManager().getMesh(name);
        WireframeMeshInstance *instance = new WireframeMeshInstance(m);

        Material *mat = info.getDefaultMaterial();

        instance->changeMaterial(mat);
        mesh->setValue(instance);
        info.registerObject(instance);
    }

    BaseNode::enable(caller);
}




