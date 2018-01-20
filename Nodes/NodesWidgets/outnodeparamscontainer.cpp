#include "outnodeparamscontainer.h"

OutNodeParamsContainer::OutNodeParamsContainer(OutNodeWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{

}

const void *OutNodeParamsContainer::getValue()
{
    OutNodeWidget *widget = (OutNodeWidget *)getParamsPanel();

    if(widget)
    {
        data.path = widget->getPath();
        data.res = widget->getRes();
        data.bRender = widget->getRender();

        return &data;
    }

    return nullptr;
}
