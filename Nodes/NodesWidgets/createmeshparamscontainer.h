#ifndef CREATEMESHPARAMSCONTAINER_H
#define CREATEMESHPARAMSCONTAINER_H

#include "../nodeparamscontainer.h"
#include "./createmeshwidget.h"

class CreateMeshParamsContainer : public NodeParamsContainer
{
public:
    CreateMeshParamsContainer(CreateMeshWidget *paramsPanel);
    ~CreateMeshParamsContainer() {}

    const void *getValue() override;

private:
    QString data;
};

#endif // CREATEMESHPARAMSCONTAINER_H
