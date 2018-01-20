#include "floatdata.h"

FloatData::FloatData(QWidget *parent): NodeData(parent), data(0.f)
{
    visualPrepare("float");
}

FloatData::~FloatData()
{
}

bool FloatData::isPresent() const
{
    return true;
}

const void *FloatData::getData()
{
    return &data;
}

void FloatData::setData(const void *newData)
{
    data = *((double *)(newData));
}

const char *FloatData::dataType() const
{
    return typeid(double).name();
}

const char *FloatData::dataType_s()
{
    return typeid(double).name();
}
