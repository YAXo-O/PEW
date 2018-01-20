#include <QPainter>
#include "../datapin.h"
#include "readwritestate.h"

ReadWriteState::ReadWriteState(DataPin *parent): DataPinState(parent)
{
}

ReadWriteState::~ReadWriteState()
{
}

const void *ReadWriteState::readValue()
{
    return getParent()->getData() ? getParent()->getData()->getData() : nullptr;
}

void ReadWriteState::writeValue(void *value)
{
    if(getParent() && getParent()->getData())
        getParent()->getData()->setData(value);
}

void ReadWriteState::paint(QPainter *p)
{
    int wid2 = getParent()->width()/2;
    int hei2 = getParent()->height()/2;

    QPoint points[4];
    points[0].setX(wid2);
    points[0].setY(0);
    points[1].setX(getParent()->width());
    points[1].setY(hei2);
    points[2].setX(wid2);
    points[2].setY(getParent()->height());
    points[3].setX(0);
    points[3].setY(hei2);

    p->drawPolygon(points, 4);
}
