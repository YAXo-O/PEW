#include <QPainter>
#include <QImage>
#include <QStyleOption>
#include "viewport.h"
#include "worldinfo.h"

#include <QDebug>

Viewport::Viewport(QWidget *parent): PEWWidget(parent)
{
}

void Viewport::paintEvent(QPaintEvent *pe)
{
    QImage *frame;
    WorldInfo::getInstance().getNodeView()->getBuffer(frame);

    QPainter p(this);
    if(frame)
        p.drawImage(0, 0, *frame);
    setUpStyle(p);
    p.end();

    // Painting gray because of async stuff;
    // We get buffer before it was changed;
    QWidget::paintEvent(pe);
}

void Viewport::setUpStyle(QPainter &p)
{
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
