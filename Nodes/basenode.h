#ifndef BASENODE_H
#define BASENODE_H

#include <QLabel>
#include <QHash>
#include <QMap>
#include <QGroupBox>
#include "movable.h"
#include "input.h"
#include "output.h"
#include "datapin.h"

const int movableNode = 2;

class BaseNode : public Movable
{
    Q_OBJECT
public:
    explicit BaseNode(QString nodeName = "Node", QWidget *parent = nullptr);

    void setName(QString &name);
    void setName(QString &&name);
    QString getName();

    void addInput(QString name, QString slotName) throw(std::out_of_range);
    void addOutput(QString name, QString signalName) throw(std::out_of_range);
    void addDataPin(DataPin *pin) throw(std::out_of_range);
    Input *getInput(const QString &slotName);
    Input *getInput(const QString &&slotName);
    Output *getOutput(const QString &signalName);
    Output *getOutput(const QString &&signalName);
    DataPin *getPin(const QString &pinName);
    DataPin *getPin(const QString &&pinName);

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
    void rearangePins();

    void appendExternalParamsWidget(QWidget *wid);

private:
    QGroupBox *externVars;
    QString nodeName;
    QLabel *nameLab;

    QMap<QString, Input *> inputs;
    QMap<QString, Output *> outputs;
    QMap<QString, DataPin *> pins;

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
