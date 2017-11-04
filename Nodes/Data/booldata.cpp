#include <QLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "booldata.h"

BoolData::BoolData(QWidget *parent): NodeData(parent)
{
    visualPrepare("bool");
    QGroupBox *box = new QGroupBox();
    box->setLayout(new QVBoxLayout());
    box->layout()->addWidget(&dataWidget);
    box->setTitle("Boolean value");
    getParamPanel()->layout()->addWidget(box);
}

BoolData::~BoolData()
{
}

const void *BoolData::getData()
{
    data = dataWidget.isChecked();
    return &data;
}

void BoolData::setData(const void *newData)
{
    dataWidget.setValue(*((bool *)(newData)));
}

const char *BoolData::dataType() const
{
    return typeid(bool).name();
}

const char *BoolData::dataType_s()
{
    return typeid(bool).name();
}
