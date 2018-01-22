#ifndef COLORPARAMSCONTAINER_H
#define COLORPARAMSCONTAINER_H

#include <QColor>

#include "../nodeparamscontainer.h"
#include "./colordatawidget.h"

class ColorParamsContainer : public NodeParamsContainer
{
public:
    ColorParamsContainer(ColorDataWidget *paramsPanel);

    const void *getValue() override;

private:
    QColor data;
};

#endif // COLORPARAMSCONTAINER_H
