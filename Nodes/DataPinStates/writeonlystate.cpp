#include <QPainter>
#include "writeonlystate.h"

WriteOnlyState::WriteOnlyState(QWidget *parent): DataPinState(parent)
{

}

WriteOnlyState::~WriteOnlyState()
{
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
