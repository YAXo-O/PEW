#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QList>
#include "pewwidget.h"
#include "Nodes/basenode.h"
#include "Nodes/outnode.h"
#include "Nodes/nodeconnection.h"
#include "Nodes/datapin.h"
#include "Nodes/nodedata.h"
#include "Nodes/dataconnection.h"

class NodeView : public PEWWidget
{
    Q_OBJECT
public:
    explicit NodeView(QWidget *parent = nullptr);
    ~NodeView();

    void addMovable(Movable *movable);
    void removeMovable(Movable *movable);
    void deleteMovable(Movable *&movable);

    const QList<NodeConnection *>::const_iterator nodeConnectionsBegin() const;
    const QList<NodeConnection *>::const_iterator nodeConnectionsEnd() const;

    NodeConnection *getCurrentConnection() const;
    const DataConnection &getCurrentDataConnection() const;

public slots:
    void movableSelected(Movable *movable);
    void getBuffer(QImage *&buffer);
    void startConnectionData(DataPin *pin);
    void endConnectionData(NodeData *node);
    void resetConnectionData();

private slots:
    void connectionStarts(BaseNode *starter, const QString &signal);
    void connectionEnds(BaseNode *receiver, const QString &slot);

protected:
    void mousePressEvent(QMouseEvent *me) override;
    void mouseMoveEvent(QMouseEvent *me) override;

private:
    Movable *currentMovable;
    OutNode *renderer;

    NodeConnection *currentConnection; // Current connection, that is being created
    DataConnection currentDataConnection; // Current data connection being created

    QList<BaseNode *> freeNodes; // Unconnected nodes (nodes with no input)
    QList<NodeConnection *> nConnections; // All node connections being made so far
};

#endif // NODEVIEW_H
