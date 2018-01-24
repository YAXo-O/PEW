#include "creatematerial.h"
#include "../externalvariablefactory.h"
#include "../Data/materialdata.h"
#include "../../Model/wireframemeshinstance.h"
#include "../Data/wireframemeshinstancedata.h"

CreateMaterial::CreateMaterial(QString name, QWidget *parent): BaseNode(name, parent),
    wid(new MaterialParamsContainer(new MaterialDataWidget))
{
    material = ExternalVariableFactory::createExternal(MaterialData::dataType_s(), "Material", DFF_WRITE);

    addDataPin(material->getPin());

    appendParamsWidget(wid->getParamsPanel());

    rearangePins();
}

void CreateMaterial::enable(BaseNode *caller)
{
    if(!material->isDataPresent() && material->isConnected())
    {
        Material *mat = new Material;
        *mat = *((Material *)wid->getValue());
        material->setValue(mat);
    }


    BaseNode::enable(caller);
}
