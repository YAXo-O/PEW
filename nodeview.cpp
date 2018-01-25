#include <QMouseEvent>
#include <QPainter>
#include "nodeview.h"
#include "worldinfo.h"

#include "Nodes/Data/alldata.h"
#include "Nodes/BasicNodes/actions.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

NodeView::NodeView(QWidget *parent): PEWWidget(parent), currentMovable(nullptr), renderer(new OutNode("Renderer")),
    currentConnection(nullptr), currentDataConnection(nullptr)
{
    addMovable(renderer);
    renderer->move(200, 200);

    initMenu();
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
        connect(this, SIGNAL(resetMovables()), movable, SLOT(resetMovable()));
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
        disconnect(movable, SLOT(resetMovable()));
        if(movable == currentMovable)
            deselectMovable();
        movable->setParent(nullptr);

        bool bUpdate = false;
        if(movable->type() == movableNode)
        {
            freeNodes.removeOne(static_cast<BaseNode *>(movable));
            for(auto i = nodeConnectionsBegin(); i != nodeConnectionsEnd(); i++)
                if((*i)->getStart()->parentWidget() == movable || (*i)->getEnd()->parentWidget() == movable)
                {
                    nConnections.removeOne(*i);
                    delete (*i);
                    bUpdate = true;
                }

            for(auto i = dataConnectionsBegin(); i != dataConnectionsEnd(); i++)
                if((*i)->getPin()->parentWidget() == static_cast<QWidget *>(movable))
                {
                    dConnections.removeOne(*i);
                    delete (*i);
                    bUpdate = true;
                }
        }
        else if(movable->type() == movableData)
        {
            for(auto i = dataConnectionsBegin(); i != dataConnectionsEnd(); i++)
                if((*i)->getData() == movable)
                {
                    dConnections.removeOne(*i);
                    delete (*i);
                    bUpdate = true;
                }
        }

        if(bUpdate)
            repaint();


    }
}

void NodeView::deleteMovable(Movable *&movable)
{
    removeMovable(movable);
    delete movable;
    movable = nullptr;
}

void NodeView::killMovable(Movable *movable)
{
    if(movable == renderer)
        return;

    removeMovable(movable);
    if(movable->getDeletable())
        delete movable;
}

const QList<NodeConnection *>::const_iterator NodeView::nodeConnectionsBegin() const
{
    return nConnections.cbegin();
}

const QList<NodeConnection *>::const_iterator NodeView::nodeConnectionsEnd() const
{
    return nConnections.end();
}

const QList<DataConnection *>::const_iterator NodeView::dataConnectionsBegin() const
{
    return dConnections.begin();
}

const QList<DataConnection *>::const_iterator NodeView::dataConnectionsEnd() const
{
    return dConnections.end();
}

void NodeView::movableSelected(Movable *movable)
{
    if((movable != currentMovable) && currentMovable)
        currentMovable->becomeInactive();

    currentMovable = movable;
}

void NodeView::getBuffer(QImage *&buffer)
{
    renderer->renderFrame(buffer);
}

void NodeView::startConnectionData(DataPin *pin)
{
    if(currentConnection)
        return;
    if(!currentDataConnection)
        currentDataConnection = new DataConnection();
    if(!pin && currentDataConnection->getPin())
        resetConnectionData();
    else if(!currentDataConnection->getPin())
        currentDataConnection->setPin(pin);
}

void NodeView::endConnectionData(NodeData *node)
{
    if(!currentDataConnection)
        return;
    if(!node && currentDataConnection->getData())
        resetConnectionData();
    else if(node && currentDataConnection->getPin())
    {
        if(node->dataType() != currentDataConnection->getPin()->getType())
            return;
        if(currentDataConnection->getData())
            delete currentDataConnection->getData();
        currentDataConnection->setData(node);
        currentDataConnection->getPin()->setData(node);
        node->setDeletable(false);
        dConnections.append(currentDataConnection);
        currentDataConnection = nullptr;

    }
}

void NodeView::resetConnectionData()
{
    currentDataConnection->setData(nullptr);
    currentDataConnection->setPin(nullptr);
}

void NodeView::simulate()
{
    for(auto i:freeNodes)
        i->enable();
}

void NodeView::connectionStarts(BaseNode *starter, const QString &signal)
{
    if(currentDataConnection)
        return;
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
        else if(currentDataConnection && currentDataConnection->getPin() && currentDataConnection->getData())

        {
            delete currentDataConnection->getData();
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
    else if(currentDataConnection)
    {
        if(currentDataConnection->getData())
            currentDataConnection->getData()->move(me->pos());
        else
        {
            NodeData *node = new NodeData();
            node->move(me->pos());
            currentDataConnection->setData(node);
        }
        repaint();
    }
}

void NodeView::contextMenuEvent(QContextMenuEvent *ce)
{
    contextMenu.exec(ce->globalPos());
}

void NodeView::initMenu()
{
    contextMenu.addAction("Create Node");
    contextMenu.addSeparator();

    contextManager.setActionMenu(contextMenu.addMenu("Action"));
    contextManager.setVariableMenu(contextMenu.addMenu("Variable"));

    createBaseActions();
    createBaseVars();
}

void NodeView::createBaseVars()
{
    // Creating basic vars

    contextManager.addVariable("Bool", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        BoolData *data = new BoolData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Int", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        IntData *data = new IntData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Float", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        FloatData *data = new FloatData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Vector", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        VectorData *data = new VectorData();
        nv->addMovable(data);
        data->move(nv->convertSpace(pos));

    }));

    contextManager.addVariable("Camera", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CameraData *data = new CameraData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Light", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        LightData *data = new LightData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Scene Object", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        SceneObjectData *data = new SceneObjectData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Color", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        ColorData *data = new ColorData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("WireframeMeshInstance", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        WireframeMeshInstanceData *data = new WireframeMeshInstanceData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Material", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        MaterialData *data = new MaterialData();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Objects Array", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        ObjectsArray *data = new ObjectsArray();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

    contextManager.addVariable("Particle System", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        ParticleSystem *data = new ParticleSystem();
        nv->addMovable(data);
        data->move(pos - nv->pos());

    }));

}

void NodeView::createBaseActions()
{
    contextManager.addAction("Create Camera", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CreateCamera *node = new CreateCamera();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Create Light", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CreateOmniLight *node = new CreateOmniLight();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Create WireframeMeshInstance", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CreateMesh *node = new CreateMesh();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Create Material", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CreateMaterial *node = new CreateMaterial();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Set Material", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        SetMaterial *node = new SetMaterial();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Append Mesh", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        AppendMesh *node = new AppendMesh();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Create Particle System", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        CreateParticleSystem *node = new CreateParticleSystem();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

    contextManager.addAction("Add Force", action([](QPoint pos)
    {
        NodeView *nv = WorldInfo::getInstance().getNodeView();
        Force *node = new Force();
        nv->addMovable(node);
        node->move(pos - nv->pos());
    }));

}

NodeConnection *NodeView::getCurrentConnection() const
{
    return currentConnection;
}

DataConnection *NodeView::getCurrentDataConnection() const
{
    return currentDataConnection;
}

void NodeView::deselectMovable()
{
    if(!currentMovable)
        return;

    currentMovable->becomeInactive();
    currentMovable = nullptr;
}

void NodeView::selectMovable(Movable *newSelection)
{
    if(!newSelection)
        return;

    currentMovable = newSelection;
    currentMovable->becomeActive();
}

ContextMenuManager &NodeView::getManager()
{
    return contextManager;
}

QPoint NodeView::convertSpace(QPoint global)
{
    return global - pos();
}
