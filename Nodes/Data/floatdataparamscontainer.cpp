#include "floatdataparamscontainer.h"

FloatDataParamsContainer::FloatDataParamsContainer(FloatDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{
}

const void *FloatDataParamsContainer::getValue()
{
    FloatDataWidget *widget = (FloatDataWidget *)getParamsPanel();

    if(widget)
    {
        data = widget->getValue();
        return &data;
    }

    return nullptr;
}


