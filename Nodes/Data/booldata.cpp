#include "booldata.h"

BoolData::BoolData(QWidget *parent): NodeData(parent), data(false)
{
    visualPrepare("bool");
}

BoolData::~BoolData()
{
}

const void *BoolData::getData() const
{
    return &data;
}

void BoolData::setData(const void *newData)
{
    data = *((bool *)(newData));
}

const char *BoolData::dataType() const
{
    return typeid(bool).name();
}

const char *BoolData::dataType_s()
{
    return typeid(bool).name();
}
