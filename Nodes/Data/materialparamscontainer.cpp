#include "materialparamscontainer.h"

MaterialParamsContainer::MaterialParamsContainer(MaterialDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{  
}

const void *MaterialParamsContainer::getValue()
{
    MaterialDataWidget *wid = (MaterialDataWidget *)(getParamsPanel());
    if(wid)
    {
        data = wid->getValue();

        return &data;
    }

    return nullptr;
}

/*

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

*/
