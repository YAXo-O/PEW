#include "createmeshparamscontainer.h"

CreateMeshParamsContainer::CreateMeshParamsContainer(CreateMeshWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{

}

const void *CreateMeshParamsContainer::getValue()
{
    CreateMeshWidget *wid = (CreateMeshWidget *)getParamsPanel();
    if(wid)
    {
        data = wid->getPath();

        return (const void *)&data;
    }

    return nullptr;
}
