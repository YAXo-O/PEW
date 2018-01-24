#ifndef CREATEMATERIAL_H
#define CREATEMATERIAL_H

#include "../externalvariable.h"
#include "../basenode.h"
#include "../Data/materialparamscontainer.h"

class CreateMaterial : public BaseNode
{
    Q_OBJECT
public:
    explicit CreateMaterial(QString name = "Create Material", QWidget *parent = nullptr);
    virtual ~CreateMaterial() {}

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *material;

    MaterialParamsContainer *wid;
};

#endif // CREATEMATERIAL_H
