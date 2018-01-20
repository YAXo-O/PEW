#ifndef OUTNODE_H
#define OUTNODE_H

#include <QTimer>
#include "basenode.h"
#include "../CompulsorySceneObjects/camera.h"

class ExternalVariable;

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
    ExternalVariable *cam;
    QTimer refreshTimer;
};

#endif // OUTNODE_H
