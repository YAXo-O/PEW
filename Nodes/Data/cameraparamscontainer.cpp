#include "cameraparamscontainer.h"

CameraParamsContainer::CameraParamsContainer(CameraDataWidget *paramsPanel): NodeParamsContainer(paramsPanel)
{
}

const void *CameraParamsContainer::getValue()
{
    CameraDataWidget *widget = (CameraDataWidget*)getParamsPanel();

    if(widget)
    {
        data.pitch = widget->getPitch();
        data.roll = widget->getRoll();
        data.yaw = widget->getYaw();
        data.location = widget->getLocation();
        data.fov = widget->getFov();

        return &data;
    }

    return nullptr;
}
