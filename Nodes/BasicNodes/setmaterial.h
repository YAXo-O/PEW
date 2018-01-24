#ifndef SETMATERIAL_H
#define SETMATERIAL_H

#include "../basenode.h"
#include "../externalvariable.h"
/*
public slots:
    void enable(BaseNode *caller) override;
*/

class SetMaterial : public BaseNode
{
    Q_OBJECT
public:
    explicit SetMaterial(QString name = "Set Material", QWidget *parent = nullptr);
    virtual ~SetMaterial() {}

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *material;
    ExternalVariable *mesh;
};

#endif // SETMATERIAL_H
