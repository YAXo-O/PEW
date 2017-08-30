#include <QPainter>
#include "readonlystate.h"

ReadOnlyState::ReadOnlyState(QWidget *parent): DataPinState(parent)
{
}

ReadOnlyState::~ReadOnlyState()
{
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
