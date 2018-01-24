#include "setmaterial.h"
#include "../externalvariablefactory.h"
#include "../Data/materialdata.h"
#include "../Data/wireframemeshinstancedata.h"

SetMaterial::SetMaterial(QString name, QWidget *parent): BaseNode(name, parent)
{
    material = ExternalVariableFactory::createExternal(MaterialData::dataType_s(), "Material", DFF_READ);
    mesh = ExternalVariableFactory::createExternal(WireframeMeshInstanceData::dataType_s(), "Mesh", DFF_BOTH);

    addDataPin(material->getPin());
    addDataPin(mesh->getPin());

    rearangePins();
}

void SetMaterial::enable(BaseNode *caller)
{
    if(material->isDataPresent() && mesh->isDataPresent())
    {
        WireframeMeshInstance *meshData = (WireframeMeshInstance *)(mesh->getValue());
        Material *mat = new Material;
        *mat = *(Material *)(material->getValue());

        meshData->changeMaterial(mat);
    }

    BaseNode::enable(caller);
}
