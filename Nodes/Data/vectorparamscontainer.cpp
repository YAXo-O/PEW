#include "vectorparamscontainer.h"

VectorParamsContainer::VectorParamsContainer(VectorDataWidget *paramsContainer): NodeParamsContainer(paramsContainer)
{
}

const void *VectorParamsContainer::getValue()
{
    VectorDataWidget *wid = (VectorDataWidget *)(getParamsPanel());
    if(wid)
    {
        data = wid->getValue();

        return &data;
    }

    return nullptr;

}
