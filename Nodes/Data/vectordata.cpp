#include "vectordata.h"

VectorData::VectorData(QWidget *parent): NodeData(parent), data(0, 0, 0)
{
    visualPrepare("vector");
}

VectorData::~VectorData()
{
}

const void *VectorData::getData()
{
    return &data;
}

void VectorData::setData(const void *newData)
{
    data = *((QVector3D *)(newData));
}

const char *VectorData::dataType() const
{
    return typeid(QVector3D).name();
}

const char *VectorData::dataType_s()
{
    return typeid(QVector3D).name();
}

