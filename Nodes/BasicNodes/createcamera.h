#ifndef CREATECAMERA_H
#define CREATECAMERA_H

#include "../basenode.h"
#include "../externalvariable.h"

class CreateCamera : public BaseNode
{
    Q_OBJECT
public:
    explicit CreateCamera(QString nodeName = "Create Camera", QWidget *parent = nullptr);

public slots:
    void enable(BaseNode *caller = nullptr) override;

private:
    ExternalVariable *camera;
};

#endif // CREATECAMERA_H
