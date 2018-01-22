#ifndef FLOATDATAPARAMSCONTAINER_H
#define FLOATDATAPARAMSCONTAINER_H

#include "../nodeparamscontainer.h"
#include "./floatdatawidget.h"

class FloatDataParamsContainer : public NodeParamsContainer
{
public:
    FloatDataParamsContainer(FloatDataWidget *paramsPanel);

    const void *getValue() override;

private:
    float data;
};

#endif // FLOATDATAPARAMSCONTAINER_H
