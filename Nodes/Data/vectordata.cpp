#include "vectordata.h"

VectorData::VectorData(QWidget *parent): NodeData(parent), data(0, 0, 0)
{
    visualPrepare("vector");

    appendParamsWidget(&wid);
    connect(&wid, &VectorDataWidget::valueChanged, [this](const QVector3D &value)mutable
    {
        data = value;
        debugVector(data);
    });

    debugVector(data);
}

VectorData::~VectorData()
{
}

bool VectorData::isPresent() const
{
    return true;
}

const void *VectorData::getData()
{
    data = wid.getValue();
    return &data;
}

void VectorData::setData(const void *newData)
{
    data = *((QVector3D *)(newData));
    wid.setValue(data);
    debugVector(data);
}

const char *VectorData::dataType() const
{
    return typeid(QVector3D).name();
}

const char *VectorData::dataType_s()
{
    return typeid(QVector3D).name();
}

void VectorData::debugVector(const QVector3D &value)
{
    setDebugValue(QString::asprintf("{%lf;%lf;%lf}", value.x(), value.y(), value.z()));
}
