#include <QPainter>
#include "arrowdrawingmanager.h"

ArrowDrawingManager::ArrowDrawingManager(NodeView *_parent): QGraphicsEffect(), parent(_parent),
    signalSelected(Qt::yellow), signalDeselected(Qt::darkBlue),
    dataSelected(Qt::yellow), dataDeselected(Qt::darkGreen)
{
}

void ArrowDrawingManager::draw(QPainter *painter)
{
    // Drawing widget itself
    QPoint offset;
    QPixmap pixmap = sourcePixmap( Qt::LogicalCoordinates, &offset);
    painter->drawPixmap(offset, pixmap);

    // Drawing connecting lines
    painter->save();

    painter->restore();
}
