#include <QPainter>
#include "arrowdrawingmanager.h"
#include "../Nodes/pinproperties.h"

#include <QDebug>

ArrowDrawingManager::ArrowDrawingManager(NodeView *_parent): QGraphicsEffect(), parent(_parent),
    signalSelected(Qt::yellow), signalDeselected(Qt::darkBlue), signalDeselectedFired(200, 100, 0),
    dataSelected(Qt::yellow), dataDeselected(Qt::darkGreen),
    signalCurrent(Qt::red)
{
}

void ArrowDrawingManager::draw(QPainter *painter)
{
    // Drawing widget itself
    QPoint offset;
    QPixmap pixmap = sourcePixmap( Qt::LogicalCoordinates, &offset);
    painter->drawPixmap(offset, pixmap);

    painter->save();

    drawNodeLines(painter);
    drawCurrentNodeLine(painter);
    drawDataLines(painter);
    drawCurrentDataLine(painter);

    painter->restore();
}

void ArrowDrawingManager::drawNodeLines(QPainter *painter)
{
    for(auto i = parent->nodeConnectionsBegin(); i != parent->nodeConnectionsEnd(); i++)
    {
        if((*i)->hasFired())
            painter->setPen(signalDeselectedFired);
        else
            painter->setPen(signalDeselected);

        QPoint start = (*i)->getStart()->parentWidget()->pos();
        start += (*i)->getStart()->pos() + pinCenter;
        QPoint end = (*i)->getEnd()->parentWidget()->pos();
        end += (*i)->getEnd()->pos() + pinCenter;

        painter->drawLine(start, end);
    }
}

void ArrowDrawingManager::drawCurrentNodeLine(QPainter *painter)
{
    if(parent->getCurrentConnection())
    {
        Output *out = parent->getCurrentConnection()->getStart();
        Input *in = parent->getCurrentConnection()->getEnd();
        if(out && in)
        {
            QPoint start = out->parentWidget()->pos();
            start += out->pos() + pinCenter;
            painter->setPen(signalCurrent);
            painter->drawLine(start, in->pos());
        }
    }
}

void ArrowDrawingManager::drawDataLines(QPainter *painter)
{
}

void ArrowDrawingManager::drawCurrentDataLine(QPainter *painter)
{
    if(parent->getCurrentDataConnection().getPin() && parent->getCurrentDataConnection().getData())
    {
        DataPin *pin = parent->getCurrentDataConnection().getPin();
        NodeData *node = parent->getCurrentDataConnection().getData();
        if(pin && node)
        {
            QPoint start = pin->pos() + pin->parentWidget()->pos() + QPoint(pinSize.width()/2, pinSize.height()/2);
            QPoint end = node->pos();

            painter->setPen(pin->getColor());
            painter->drawLine(start, end);
        }
    }
}
