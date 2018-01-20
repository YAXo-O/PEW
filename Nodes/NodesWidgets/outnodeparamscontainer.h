#ifndef OUTNODEPARAMSCONTAINER_H
#define OUTNODEPARAMSCONTAINER_H


#include "../nodeparamscontainer.h"
#include "../../CompulsorySceneObjects/cameraoptions.h"
#include "outnodewidget.h"

class OutNodeParamsContainer: public NodeParamsContainer
{
public:
    OutNodeParamsContainer(OutNodeWidget *paramsPanel);
    ~OutNodeParamsContainer() {}

    const void *getValue() override;

private:
    renderOptions data;
};

#endif // OUTNODEPARAMSCONTAINER_H
