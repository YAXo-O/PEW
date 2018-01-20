#include <QPainter>
#include <QThread>
#include "outnode.h"
#include "../worldinfo.h"
#include "externalvariablefactory.h"
#include "Nodes/Data/cameradata.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

OutNode::OutNode(QString nodeName, QWidget *parent): BaseNode(nodeName, parent), frame(nullptr),
    cam(ExternalVariableFactory::createExternal(CameraData::dataType_s(), "Camera", DFF_BOTH))
{
    addDataPin(cam->getPin());
    rearangePins();
}

OutNode::~OutNode()
{
    delete frame;
}

void OutNode::renderFrame(QImage *&_frame)
{
    _frame = frame;
}

void OutNode::enable(BaseNode *)
{
    // Updating frame
    if(frame)
        delete frame;
    frame = new QImage(WorldInfo::getInstance().getViewport()->size(), QImage::Format_ARGB32);

    Camera *camera = nullptr;
    if(cam && cam->isDataPresent())
        camera = (Camera*)(cam->getValue());

    // Check if we can view from camera, or not
    if(!camera)
    {
        QPainter p(frame);

        p.setPen(Qt::green);
        p.drawLine(0, 0, frame->width(), frame->height());
        p.drawLine(frame->width(), 0, 0, frame->height());

        // Calculation for central alignment
        p.setPen(Qt::red);
        p.drawText(QRect(0, 0, frame->width(), frame->height()), Qt::AlignCenter, "No camera specified!");

        p.end();
    }
    else
    {
        camera->setSize(frame->size());
        camera->setResolution(frame->size());
        camera->renderScene(*frame);
    }

    BaseNode::enable();
    WorldInfo::getInstance().getViewport()->repaint();
}
