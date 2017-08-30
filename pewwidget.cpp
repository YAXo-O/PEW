#include <QResizeEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include "pewwidget.h"

PEWWidget::PEWWidget(QWidget *parent) : QWidget(parent), resizeDirection(RD_NONE),
    borderWidth(1), borderColor(Qt::black),
    activeBorderWidth(1), activeBorderColor(Qt::yellow),
    currentWidth(borderWidth), currentColor(borderColor), bActive(false)
{
    setMouseTracking(true);
}

void PEWWidget::setBorder(QColor col, int wid)
{
    borderColor = col;
    borderWidth = wid;
}

void PEWWidget::setActiveBorder(QColor col, int wid)
{
    activeBorderColor = col;
    activeBorderWidth = wid;
}

bool PEWWidget::isCurrent() const
{
    return bActive;
}

void PEWWidget::receiveActive(PEWWidget *wid)
{
    if(wid != this)
        becomeInactive();

}

void PEWWidget::mousePressEvent(QMouseEvent *)
{
    if(!bActive)
    {
        bActive = true;
        currentColor = activeBorderColor;
        currentWidth = activeBorderWidth;

        emit becameActive(this);
        repaint();
    }
}

void PEWWidget::mouseMoveEvent(QMouseEvent *me)
{
    if((me->buttons() & Qt::LeftButton) && resizeDirection != RD_NONE)
        mouseResizeMove(me);
    else
        mouseUnpressedMove(me);

    QWidget::mouseMoveEvent(me);
}

void PEWWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setPen(QPen(QBrush(currentColor), currentWidth));
    p.drawRect(0, 0, width() - 1, height() - 1);

    p.end();
}

void PEWWidget::mouseUnpressedMove(QMouseEvent *me)
{
    if(abs(me->x() - width()) <= 10)
    {
        if(abs(me->y() - height()) <= 10)
        {
            setCursor(Qt::SizeFDiagCursor);
            resizeDirection = RD_DIAG;
        }
        else
        {
            setCursor(Qt::SizeHorCursor);
            resizeDirection = RD_X;
        }
    }
    else if(abs(me->y() - height()) <= 10)
    {
        setCursor(Qt::SizeVerCursor);
        resizeDirection = RD_Y;
    }
    else if(resizeDirection != RD_NONE)
    {
        setCursor(Qt::ArrowCursor);
        resizeDirection = RD_NONE;
    }
}

void PEWWidget::mouseResizeMove(QMouseEvent *me)
{
    int wid = me->x() - x();
    int hei = me->y() - y();
    if(wid <= 0)
        wid = width();
    if(hei <= 0)
        hei = height();

    switch(resizeDirection)
    {
    case RD_X:
        setFixedWidth(wid);
        break;

    case RD_Y:
        setFixedHeight(hei);
        break;

    case RD_DIAG:
        setFixedSize(wid, hei);
        break;

    default:
        break;
    }
}

void PEWWidget::becomeInactive()
{
    currentColor = borderColor;
    currentWidth = borderWidth;
    bActive = false;

    repaint();
}
