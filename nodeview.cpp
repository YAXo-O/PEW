#include <QMouseEvent>
#include <QPainter>
#include "nodeview.h"
#include "Nodes/nodedata.h"
#include "Nodes/BasicNodes/testnode.h"

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
    currentConnection(nullptr)
{
     addMovable(renderer);
     addMovable(new TestNode("Base"));
     addMovable(new BoolData());
     renderer->move(200, 200);
}

NodeView::~NodeView()
{
    if(currentConnection)
        delete currentConnection;
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

const QList<NodeConnection *>::const_iterator NodeView::nodeConnectionsBegin() const
{
    return nConnections.cbegin();
}

const QList<NodeConnection *>::const_iterator NodeView::nodeConnectionsEnd() const
{
    return nConnections.end();
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

void NodeView::startConnectionData(DataPin *pin)
{
    if(!pin && currentDataConnection.getPin())
        resetConnectionData();
    else if(!currentDataConnection.getPin())
        currentDataConnection.setPin(pin);
}

void NodeView::endConnectionData(NodeData *node)
{
    if(!node && currentDataConnection.getData())
        resetConnectionData();
    else if(node && currentDataConnection.getPin())
    {
        if(currentDataConnection.getData())
            delete currentDataConnection.getData();
        currentDataConnection.setData(node);
        currentDataConnection.getPin()->setData(node);
        resetConnectionData();
    }
}

void NodeView::resetConnectionData()
{
    currentDataConnection.setData(nullptr);
    currentDataConnection.setPin(nullptr);
}

void NodeView::connectionStarts(BaseNode *starter, const QString &signal)
{
    if(currentConnection)
        currentConnection->setStart(starter->getOutput(signal));
    else
        currentConnection = new NodeConnection(starter->getOutput(signal));

    connect(starter, QString("2" + signal).toStdString().data(), currentConnection, SLOT(fire(BaseNode*)));
}

void NodeView::connectionEnds(BaseNode *receiver, const QString &slot)
{
    if(!currentConnection || !currentConnection->getStart())
        return;

    // Cleaning from temporary line
    delete currentConnection->getEnd();

    currentConnection->setEnd(receiver->getInput(slot));
    connect(currentConnection, SIGNAL(fired(BaseNode*)), receiver, QString("1" + slot).toStdString().data());
    nConnections.append(currentConnection);
    currentConnection = nullptr;

    freeNodes.removeOne(receiver);
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
    {
        if(currentConnection)
        {
            delete currentConnection->getEnd();
            delete currentConnection;
            currentConnection = nullptr;
            repaint();
        }
        else if(currentDataConnection.getPin() && currentDataConnection.getData())

        {
            delete currentDataConnection.getData();
            resetConnectionData();
            repaint();
        }
    }
}

void NodeView::mouseMoveEvent(QMouseEvent *me)
{
    if(currentConnection && currentConnection->getStart())
    {
        if(currentConnection->getEnd())
            currentConnection->getEnd()->move(me->pos());
        else
        {
            Input *in = new Input("cursor");
            in->move(me->pos());
            currentConnection->setEnd(in);
        }
        repaint();
    }
    else if(currentDataConnection.getPin())
    {
        if(currentDataConnection.getData())
            currentDataConnection.getData()->move(me->pos());
        else
        {
            NodeData *node = new NodeData();
            node->move(me->pos());
            currentDataConnection.setData(node);
        }
        repaint();
    }
}

NodeConnection *NodeView::getCurrentConnection() const
{
    return currentConnection;
}

const DataConnection &NodeView::getCurrentDataConnection() const
{
    return currentDataConnection;
}
