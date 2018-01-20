#ifndef TESTNODE_H
#define TESTNODE_H

#include "../basenode.h"
#include "../externalvariable.h"

class TestNode : public BaseNode
{
public:
    explicit TestNode(QString nodeName = "Test", QWidget *parent = nullptr);
    ~TestNode() override;

public slots:
    void enable(BaseNode *caller = nullptr) override;

private:
    ExternalVariable *read;
    ExternalVariable *write;
    ExternalVariable *both;
};

#endif // TESTNODE_H
