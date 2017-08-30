#include <QPainter>
#include "outnode.h"
#include "../worldinfo.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

OutNode::OutNode(QString nodeName, QWidget *parent): BaseNode(nodeName, parent), frame(nullptr),
    cam(nullptr)
{
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

    // Check if we can view from camera, or not
    if(!cam)
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
    else if(cam->getSize() != frame->size())
    {
        cam->setSize(frame->size());
        cam->setResolution(frame->size());
        cam->renderScene(*frame);
    }

}
