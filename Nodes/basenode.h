#ifndef BASENODE_H
#define BASENODE_H

#include <QLabel>
#include <QList>
#include "movable.h"
#include "input.h"
#include "output.h"

const int movableNode = 2;

class BaseNode : public Movable
{
    Q_OBJECT
public:
    explicit BaseNode(QString nodeName = "Node", QWidget *parent = nullptr);

    void setName(QString &name);
    void setName(QString &&name);
    QString getName();

    void addInput(QString name, QString slotName);
    void addOutput(QString name, QString signalName);

    void connectToViewer(const NodeView *viewer) override;
    void disconnectFromViewer() override;

    void inputConnected();
    void inputDisconnected();

    int type() override;

protected:
    void paintEvent(QPaintEvent *pe) override;
    void setUpStyle(QPainter &p);
    void rearangeInputs();
    void rearangeOutputs();

private:
    QString nodeName;
    QLabel *nameLab;

    QList<Input *> inputs;
    QList<Output *> outputs;

    int inputCount;

public slots:
    void becomeInactive() override;
    void becomeActive() override;

    //Node can have multiple inputs, but this one is obligatory
    virtual void enable(BaseNode *caller = nullptr); // Makes node do its thing.

signals:
    void done(BaseNode *me);

};

#endif // BASENODE_H
