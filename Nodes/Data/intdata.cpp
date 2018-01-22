#include "intdata.h"

IntData::IntData(QWidget *parent): NodeData(parent), data(0)
{
    visualPrepare("int");

    appendParamsWidget(&wid);
    setDebugValue("0");

    connect(&wid, &IntDataWidget::valueChanged, [this]()mutable
    {
        data = wid.getValue();
        setDebugValue(QString::number(data));
    });
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
    data = wid.getValue();
    return &data;
}

void IntData::setData(const void *newData)
{
    data = *((int32_t *)(newData));
    wid.setValue(data);
    setDebugValue(QString::number(data));
}

const char *IntData::dataType() const
{
    return typeid(int32_t).name();
}

const char *IntData::dataType_s()
{
    return typeid(int32_t).name();
}
