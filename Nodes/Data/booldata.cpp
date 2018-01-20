#include <QLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "booldata.h"

#include <QDebug>

BoolData::BoolData(QWidget *parent): NodeData(parent), dataWidget(new BoolDataWidget)
{
    visualPrepare("bool");
    prepareParamPanel();

    connect(dataWidget, SIGNAL(stateChanged(int)), this, SLOT(repaint()));
}

BoolData::~BoolData()
{
}

bool BoolData::isPresent() const
{
    return true;
}

const void *BoolData::getData()
{
    data = dataWidget->isChecked();
    return &data;
}

void BoolData::setData(const void *newData)
{
    dataWidget->setValue(*((bool *)(newData)));
    repaint();
}

const char *BoolData::dataType() const
{
    return typeid(bool).name();
}

const char *BoolData::dataType_s()
{
    return typeid(bool).name();
}

void BoolData::paintEvent(QPaintEvent *pe)
{
    NodeData::paintEvent(pe);

    getData();
    if(data)
        setDebugValue("True");
    else
        setDebugValue("False");
}

void BoolData::prepareParamPanel()
{
    QGroupBox *box = new QGroupBox();
    box->setLayout(new QVBoxLayout());
    box->layout()->addWidget(dataWidget);
    box->setTitle("Boolean value");
    box->setMinimumHeight(75);
    appendParamsWidget(box);
}
