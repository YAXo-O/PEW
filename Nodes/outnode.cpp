#include <QPainter>
#include <QThread>
#include <QLayout>
#include <QMessageBox>
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

    OutNodeWidget *props = new OutNodeWidget;
    container = new OutNodeParamsContainer(props);
    getParamPanel()->layout()->addWidget(props);
}

OutNode::~OutNode()
{
    delete frame;
    delete container;
}

void OutNode::renderFrame(QImage *&_frame)
{
    _frame = frame;
}

void OutNode::enable(BaseNode *)
{
    WorldInfo &info = WorldInfo::getInstance();
    // Updating frame
    if(frame)
        delete frame;
    frame = new QImage(info.getViewport()->size(), QImage::Format_ARGB32);

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

        info.getViewport()->repaint();
    }
    else
    {
        // Have to create preview(for viewport)
        RenderStatus &stat = info.getRenderStatus();
        stat.setSimProgress(100 * (double(info.getCurrentFrame() + 1)/info.getFrameCount()));

        QMetaObject::Connection con;
        con = connect(camera, &Camera::drewLine,
                               [&stat, &info](float progress)mutable
                                {
                                    stat.setDisplayProgress(progress * 100);
                                    info.getViewport()->repaint();
                                });
        camera->setSize(frame->size());
        camera->setResolution(frame->size());
        camera->renderScene(*frame);
        disconnect(con);

        // And render to file
        renderOptions *options = (renderOptions *)(container->getValue());
        if(options->bRender)
        {
            QImage output(options->res, QImage::Format_RGB32);

            con = connect(camera, &Camera::drewLine,
                                   [&stat](float progress)mutable
                                    {
                                        stat.setRenderProgress(progress * 100);
                                    });

            camera->setSize(options->res);
            camera->setResolution(options->res);
            camera->renderScene(output);
            disconnect(con);


            if(!output.save(options->path + QString("frame_") + QString::number(info.getCurrentFrame()) + ".png"))
                QMessageBox::warning(this, "Write file error", "Can not write file!\n Check path and format!\n");
        }
    }

    BaseNode::enable();
    info.changeCurrentFrame(info.getCurrentFrame() + 1);
    info.simulateNext();
}
