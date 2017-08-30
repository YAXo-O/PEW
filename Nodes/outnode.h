#ifndef OUTNODE_H
#define OUTNODE_H

#include "basenode.h"
#include "../CompulsorySceneObjects/camera.h"

class OutNode : public BaseNode
{
public:
    Q_OBJECT
public:
    explicit OutNode(QString nodeName = "Render", QWidget *parent = nullptr);
    ~OutNode();
    void renderFrame(QImage *&frame);


public slots:
    void enable(BaseNode *caller = nullptr) override;

private:
    QImage *frame;
    Camera *cam;

};

#endif // OUTNODE_H
