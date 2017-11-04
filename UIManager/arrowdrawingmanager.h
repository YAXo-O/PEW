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
    QColor signalDeselectedFired;
    QColor dataSelected;
    QColor dataDeselected;
    QColor signalCurrent;

    void drawNodeLines(QPainter *painter);
    void drawCurrentNodeLine(QPainter *painter);
    void drawDataLines(QPainter *painter);
    void drawCurrentDataLine(QPainter *painter);
};

#endif // ARROWDRAWINGMANAGER_H
