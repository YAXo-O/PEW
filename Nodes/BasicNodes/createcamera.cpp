#include "../externalvariablefactory.h"
#include "createcamera.h"
#include "../Data/cameradata.h"
#include "../../worldinfo.h"
#include "../../CompulsorySceneObjects/cameraoptions.h"

CreateCamera::CreateCamera(QString nodeName, QWidget *parent): BaseNode(nodeName, parent)
{
    camera = ExternalVariableFactory::createExternal(CameraData::dataType_s(), "Camera Actor", DFF_WRITE);
    addDataPin(camera->getPin());
    appendExternalParamsWidget(camera->getParamsContainer()->getParamsPanel());
    rearangePins();
}

void CreateCamera::enable(BaseNode *caller)
{
    if(!camera->isDataPresent() && camera->isConnected())
    {
        Viewport *viewport = WorldInfo::getInstance().getViewport();
        QSize screenSize = viewport->size();
        Camera *cam = new Camera(screenSize, screenSize);

        cameraOptions *options = (cameraOptions *)(camera->getParamsContainer()->getValue());
        cam->setDirection(options->roll, options->pitch, options->yaw);
        cam->setFOV(options->fov);
        cam->setOrigin(options->location);
        camera->setValue(cam);
    }

    BaseNode::enable(caller);
}


