#include <QPainter>
#include <QDebug>
#include "../datapin.h"
#include "readonlystate.h"

ReadOnlyState::ReadOnlyState(DataPin *parent): DataPinState(parent)
{
}

ReadOnlyState::~ReadOnlyState()
{
}

const void *ReadOnlyState::readValue()
{
    return getParent()->getData() ? getParent()->getData()->getData() : nullptr;
}

void ReadOnlyState::writeValue(void *)
{
    qDebug() << "Writing is forbidden!";
}

void ReadOnlyState::paint(QPainter *p)
{
    QPoint points[3];
    points[0].setX(getParent()->width()/2);
    points[0].setY(0);
    points[1].setX(0);
    points[1].setY(getParent()->height());
    points[2].setX(getParent()->width());
    points[2].setY(getParent()->height());

    p->drawPolygon(points, 3);
}
