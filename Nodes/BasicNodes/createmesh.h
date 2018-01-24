#ifndef CREATEMESH_H
#define CREATEMESH_H

#include "../basenode.h"
#include "../externalvariable.h"
#include "../NodesWidgets/createmeshparamscontainer.h"
#include "../Data/materialparamscontainer.h"

class CreateMesh : public BaseNode
{
    Q_OBJECT
public:
    explicit CreateMesh(QString nodeName = "Create Mesh", QWidget *parent = nullptr);

public slots:
    void enable(BaseNode *caller = nullptr) override;

private:
    ExternalVariable *mesh;
    CreateMeshParamsContainer *wid;
};

#endif // CREATEMESH_H
