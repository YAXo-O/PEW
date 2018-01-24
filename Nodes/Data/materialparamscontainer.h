#ifndef MATERIALPARAMSCONTAINER_H
#define MATERIALPARAMSCONTAINER_H

#include "materialdatawidget.h"
#include "../../Model/material.h"
#include "../nodeparamscontainer.h"

class MaterialParamsContainer : public NodeParamsContainer
{
public:
    MaterialParamsContainer(MaterialDataWidget *paramsPanel);

    const void *getValue() override;

private:
    Material data;
};

#endif // MATERIALPARAMSCONTAINER_H
