#include "intdataparamscontainer.h"


IntDataParamsContainer::IntDataParamsContainer(IntDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{
}

const void *IntDataParamsContainer::getValue()
{
    IntDataWidget *wid = (IntDataWidget *)getParamsPanel();
    if(wid)
    {
        data = wid->getValue();

        return &data;
    }

    return nullptr;
}
