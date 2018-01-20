#include <QPainter>
#include <QDebug>
#include "../datapin.h"
#include "writeonlystate.h"

WriteOnlyState::WriteOnlyState(DataPin *parent): DataPinState(parent)
{
}

WriteOnlyState::~WriteOnlyState()
{
}

const void *WriteOnlyState::readValue()
{
    qDebug() << "Reading is forbidden";

    return nullptr;
}

void WriteOnlyState::writeValue(void *value)
{
    if(getParent() && getParent()->getData())
        getParent()->getData()->setData(value);
}

void WriteOnlyState::paint(QPainter *p)
{
    QPoint points[3];
    points[0].setX(getParent()->width()/2);
    points[0].setY(getParent()->height());
    points[1].setX(0);
    points[1].setY(0);
    points[2].setX(getParent()->width());
    points[2].setY(0);

    p->drawPolygon(points, 3);
}
