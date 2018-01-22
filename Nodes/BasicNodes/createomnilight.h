#ifndef CREATEOMNILIGHT_H
#define CREATEOMNILIGHT_H

#include "../basenode.h"
#include "../externalvariable.h"

class CreateOmniLight : public BaseNode
{
    Q_OBJECT

public:
    explicit CreateOmniLight(QString nodeName = "Create Omni Light", QWidget *parent = nullptr);

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *light;
    ExternalVariable *pos;
    ExternalVariable *intensity;
    ExternalVariable *color;
};

#endif // CREATEOMNILIGHT_H
