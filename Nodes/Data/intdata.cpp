#include "intdata.h"

IntData::IntData(QWidget *parent): NodeData(parent), data(0)
{
    visualPrepare("int");
}

IntData::~IntData()
{
}

bool IntData::isPresent() const
{
    return true;
}

const void *IntData::getData()
{
    return &data;
}

void IntData::setData(const void *newData)
{
    data = *((int32_t *)(newData));
}

const char *IntData::dataType() const
{
    return typeid(int32_t).name();
}

const char *IntData::dataType_s()
{
    return typeid(int32_t).name();
}
