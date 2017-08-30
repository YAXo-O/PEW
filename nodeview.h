#ifndef NODEVIEW_H
#define NODEVIEW_H

#include <QList>
#include "pewwidget.h"
#include "Nodes/basenode.h"
#include "Nodes/outnode.h"

class NodeView : public PEWWidget
{
    Q_OBJECT
public:
    explicit NodeView(QWidget *parent = nullptr);
    ~NodeView();

    void addMovable(Movable *movable);
    void removeMovable(Movable *movable);
    void deleteMovable(Movable *&movable);

public slots:
    void movableSelected(Movable *movable);
    void getBuffer(QImage *&buffer);

private slots:
    void connectionStarts(BaseNode *starter, const QString &signal);
    void connectionEnds(BaseNode *receiver, const QString &slot);

protected:
    void mousePressEvent(QMouseEvent *me) override;

private:
    Movable *currentMovable;
    OutNode *renderer;

    BaseNode *currentStarter; // Node thats starts current connection
    QString currentStarterSignal; // Starter slot

    QList<BaseNode *> freeNodes; // Unconnected nodes (nodes with no input)
};

#endif // NODEVIEW_H
