#include <QMouseEvent>
#include <QPainter>
#include "nodeview.h"
#include "Nodes/nodedata.h"

#include "Nodes/Data/booldata.h"
#include "Nodes/Data/intdata.h"
#include "Nodes/Data/floatdata.h"
#include "Nodes/Data/sceneobjectdata.h"
#include "Nodes/Data/vectordata.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

NodeView::NodeView(QWidget *parent): PEWWidget(parent), currentMovable(nullptr), renderer(new OutNode("Renderer")),
    currentStarter(nullptr), currentStarterSignal("")
{
     addMovable(renderer);
     addMovable(new BoolData);
}

NodeView::~NodeView()
{
}

void NodeView::addMovable(Movable *movable)
{
    if(movable)
    {
        movable->setParent(this);
        movable->show();
        movable->connectToViewer(this);
        if(movable->type() == movableNode)
            freeNodes.append(static_cast<BaseNode *>(movable));
    }
}

void NodeView::removeMovable(Movable *movable)
{
    if(movable && movable->parentWidget() == this)
    {
        movable->setParent(nullptr);
        movable->disconnectFromViewer();
        if(movable->type() == movableNode)
            freeNodes.removeOne(static_cast<BaseNode *>(movable));
    }
}

void NodeView::deleteMovable(Movable *&movable)
{
    removeMovable(movable);
    delete movable;
    movable = nullptr;
}

void NodeView::movableSelected(Movable *movable)
{
    if((movable != currentMovable) && currentMovable)
        currentMovable->becomeInactive();

    currentMovable = movable;
}

void NodeView::getBuffer(QImage *&buffer)
{
    for(auto i:freeNodes)
        i->enable();
    renderer->renderFrame(buffer);
}

void NodeView::connectionStarts(BaseNode *starter, const QString &signal)
{
    currentStarter = starter;
    currentStarterSignal = signal;
}

void NodeView::connectionEnds(BaseNode *receiver, const QString &slot)
{
    if(!currentStarter)
        return;

    connect(currentStarter, QString("2" + currentStarterSignal).toStdString().data(),
            receiver, QString("1" + slot).toStdString().data());
    receiver->inputConnected();
    freeNodes.removeOne(receiver);

    currentStarter = nullptr;
}

void NodeView::mousePressEvent(QMouseEvent *me)
{
    PEWWidget::mousePressEvent(me);

    if(currentMovable && (childAt(me->pos()) == nullptr))
    {
        currentMovable->becomeInactive();
        currentMovable = nullptr;
    }

    if(me->button() & Qt::RightButton)
        currentStarter = nullptr;
}
