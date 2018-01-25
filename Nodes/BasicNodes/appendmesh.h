#ifndef APPENDMESH_H
#define APPENDMESH_H

#include "../basenode.h"
#include "../externalvariable.h"

class AppendMesh : public BaseNode
{
    Q_OBJECT
public:
    explicit AppendMesh(QString name = "Append Mesh", QWidget *parent = nullptr);
    virtual ~AppendMesh();

public slots:
    void enable(BaseNode *caller) override;

private:
    ExternalVariable *array;
    ExternalVariable *mesh;

    int fireCount;
    int firedCount;
};

#endif // APPENDMESH_H
