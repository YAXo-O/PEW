#include "colordata.h"

ColorData::ColorData(QWidget *parent): NodeData(parent), data(0, 0, 0)
{
    visualPrepare("color");
    setDebugValue(data.name());

    appendParamsWidget(&wid);
}

ColorData::~ColorData()
{
}

bool ColorData::isPresent() const
{
    return true;
}

const void *ColorData::getData()
{
    data = wid.getValue();

    return &data;
}

void ColorData::setData(const void *newData)
{
    data = *((QColor *)newData);
    wid.setValue(data);
    setDebugValue(data.name());
}

const char *ColorData::dataType() const
{
    return typeid(QColor).name();
}

const char *ColorData::dataType_s()
{
    return typeid(QColor).name();
}
