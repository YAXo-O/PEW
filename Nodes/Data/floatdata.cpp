#include <QGroupBox>
#include <QHBoxLayout>

#include "floatdata.h"

FloatData::FloatData(QWidget *parent): NodeData(parent), data(0.f)
{
    visualPrepare("float");
    setDebugValue("0");

    connect(&wid, &FloatDataWidget::valueChanged, [this](double val)mutable{data = val; setDebugValue(QString::number(val));});
    prepareParamPanel();
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
    data = wid.getValue();
    return &data;
}

void FloatData::setData(const void *newData)
{
    data = *((double *)(newData));
    setDebugValue(QString::number(data));
    wid.setValue(data);
}

const char *FloatData::dataType() const
{
    return typeid(double).name();
}

const char *FloatData::dataType_s()
{
    return typeid(double).name();
}

void FloatData::prepareParamPanel()
{
    QGroupBox *box = new QGroupBox();
    box->setLayout(new QVBoxLayout());
    box->layout()->addWidget(&wid);
    box->setTitle("Float value");
    box->setMinimumHeight(75);
    appendParamsWidget(box);
}
