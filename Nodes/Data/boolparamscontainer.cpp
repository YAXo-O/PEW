#include "boolparamscontainer.h"

BoolParamsContainer::BoolParamsContainer(BoolDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{
}

const void *BoolParamsContainer::getValue()
{
    BoolDataWidget *panel = (BoolDataWidget *)getParamsPanel();
    if(panel)
    {
        data = (void*)(panel->isChecked());
        return &data;
    }

    return nullptr;
}
