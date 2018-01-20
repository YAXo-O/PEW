#ifndef BOOLPARAMSCONTAINER_H
#define BOOLPARAMSCONTAINER_H

#include "../nodeparamscontainer.h"
#include "booldatawidget.h"

class BoolParamsContainer : public NodeParamsContainer
{
public:
    BoolParamsContainer(BoolDataWidget *paramsPanel);

    const void *getValue() override;

private:
    bool data;
};

#endif // BOOLPARAMSCONTAINER_H
