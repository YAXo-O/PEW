#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QList>
#include <QMenu>
#include "pewwidget.h"
#include "Nodes/basenode.h"
#include "Nodes/outnode.h"
#include "Nodes/nodeconnection.h"
#include "Nodes/datapin.h"
#include "Nodes/nodedata.h"
#include "Nodes/dataconnection.h"
#include "contextmenumanager.h"

class NodeView : public PEWWidget
{
    Q_OBJECT
public:
    explicit NodeView(QWidget *parent = nullptr);
    ~NodeView();

    const QList<NodeConnection *>::const_iterator nodeConnectionsBegin() const;
    const QList<NodeConnection *>::const_iterator nodeConnectionsEnd() const;
    const QList<DataConnection *>::const_iterator dataConnectionsBegin() const;
    const QList<DataConnection *>::const_iterator dataConnectionsEnd() const;

    NodeConnection *getCurrentConnection() const;
    DataConnection *getCurrentDataConnection() const;

    void deselectMovable(); // Deselect current movable;
    void selectMovable(Movable *newSelection);

    ContextMenuManager &getManager();
    QPoint convertSpace(QPoint global);

public slots:
    void movableSelected(Movable *movable);
    void getBuffer(QImage *&buffer);
    void resetConnectionData();
    void simulate();

    /* TODO:
     *  delete connections of current node
     *  inform pins and others nodes about deletion
     */
    void addMovable(Movable *movable);
    void removeMovable(Movable *movable);
    void deleteMovable(Movable *&movable);
    void killMovable(Movable *movable);

private slots:
    void connectionStarts(BaseNode *starter, const QString &signal);
    void connectionEnds(BaseNode *receiver, const QString &slot);
    void startConnectionData(DataPin *pin);
    void endConnectionData(NodeData *node);

protected:
    void mousePressEvent(QMouseEvent *me) override;
    void mouseMoveEvent(QMouseEvent *me) override;
    void contextMenuEvent(QContextMenuEvent *ce) override;

private:
    Movable *currentMovable;
    OutNode *renderer;

    NodeConnection *currentConnection; // Current connection, that is being created
    DataConnection *currentDataConnection; // Current data connection being created

    QList<BaseNode *> freeNodes; // Unconnected nodes (nodes with no input)
    QList<NodeConnection *> nConnections; // All node connections being made so far
    QList<DataConnection *> dConnections;

    QMenu contextMenu;
    ContextMenuManager contextManager;

    void initMenu();
    void createBaseVars();
    void createBaseActions();

signals:
    void resetMovables();
};

#endif // NODEVIEW_H
