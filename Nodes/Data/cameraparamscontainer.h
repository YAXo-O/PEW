#ifndef CAMERAPARAMSCONTAINER_H
#define CAMERAPARAMSCONTAINER_H

#include "../nodeparamscontainer.h"
#include "../../CompulsorySceneObjects/cameraoptions.h"
#include "cameradatawidget.h"

class CameraParamsContainer: public NodeParamsContainer
{
public:
    CameraParamsContainer(CameraDataWidget *paramsPanel);
    const void *getValue() override;

private:
    cameraOptions data;
};

#endif // CAMERAPARAMSCONTAINER_H
