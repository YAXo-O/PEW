#ifndef ARROWDRAWINGMANAGER_H
#define ARROWDRAWINGMANAGER_H

#include <QGraphicsEffect>
#include "../nodeview.h"

class ArrowDrawingManager : public QGraphicsEffect
{
    Q_OBJECT
public:
    ArrowDrawingManager(NodeView *parent);

protected:
    void draw(QPainter *painter) override;

private:
    NodeView *parent;
    QColor signalSelected;
    QColor signalDeselected;
    QColor dataSelected;
    QColor dataDeselected;
};

#endif // ARROWDRAWINGMANAGER_H
