#ifndef INTDATAPARAMSCONTAINER_H
#define INTDATAPARAMSCONTAINER_H

#include "../nodeparamscontainer.h"
#include "intdatawidget.h"

class IntDataParamsContainer : public NodeParamsContainer
{
public:
    IntDataParamsContainer(IntDataWidget *paramsPanel);

    const void *getValue() override;

private:
    int32_t data;
};

#endif // INTDATAPARAMSCONTAINER_H
