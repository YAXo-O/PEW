#include "nodeparamscontainer.h"

NodeParamsContainer::NodeParamsContainer(QWidget *paramsPanel): panel(paramsPanel)
{
}

QWidget *NodeParamsContainer::getParamsPanel() const
{
    return panel;
}

const void *NodeParamsContainer::getValue()
{
    return nullptr;
}

