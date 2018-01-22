#include "colorparamscontainer.h"

ColorParamsContainer::ColorParamsContainer(ColorDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{
}

const void *ColorParamsContainer::getValue()
{
    ColorDataWidget *wid = (ColorDataWidget *)(getParamsPanel());
    if(wid)
    {
        data = wid->getValue();

        return &data;
    }

    return nullptr;
}
