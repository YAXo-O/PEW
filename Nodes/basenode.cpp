#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include "basenode.h"
#include "../WidgetUtilities/styleloader.h"
#include "../nodeview.h"
#include "pinproperties.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

BaseNode::BaseNode(QString _nodeName, QWidget *parent) : Movable(parent), nodeName(_nodeName),
    nameLab(new QLabel(nodeName, this)), inputCount(0)
{
    QString styleSheet = StyleLoader::loadCSS(cssPath + "BaseNode.css");
    setObjectName("inactive");
    nameLab->setObjectName("nameLab");
    nameLab->setAlignment(Qt::AlignCenter);

    setStyleSheet(styleSheet);
    nameLab->setStyleSheet(styleSheet);

    nameLab->resize(150, nameLab->height());
    resize(150, 80);

    addInput("Activate", "enable(BaseNode *)");
    rearangeInputs();
    addOutput("Done", "done(BaseNode *)");
    rearangeOutputs();
}

void BaseNode::setName(QString &name)
{
    nodeName = name;
}

void BaseNode::setName(QString &&name)
{
    setName(name);
}

QString BaseNode::getName()
{
    return nodeName;
}

void BaseNode::addInput(QString name, QString slotName) throw(std::out_of_range)
{
    Input *in = new Input(name, this);
    in->setSlotName(slotName);
    QLabel *lab = new QLabel(name, this);
    lab->resize(width(), lab->fontMetrics().height());
    lab->setAlignment(Qt::AlignLeft);
    in->setLab(lab);

    if(inputs.contains(slotName))
    {
        throw std::out_of_range("Current slot is already in use");
        delete in;
        delete lab;
    }
    else
        inputs[slotName] = in;
}

void BaseNode::addOutput(QString name, QString signalName) throw(std::out_of_range)
{
    Output *out = new Output(name, this);
    out->setSignalName(signalName);
    QLabel *lab = new QLabel(name, this);
    lab->setAlignment(Qt::AlignRight);
    out->setLab(lab);

    if(outputs.contains(signalName))
    {
        throw std::out_of_range("Current slot is already in use");
        delete out;
        delete lab;
    }
    else
        outputs[signalName] = out;
}

void BaseNode::addDataPin(DataPin *pin) throw(std::out_of_range)
{
    if(!pin)
        return;

    const QString &varName = pin->getName();
    if(pins.contains(varName))
        throw std::out_of_range(QString("Pin with name " + varName + "already exists and in use!").toStdString());
    else
    {
        pin->setParent(this);
        pins[varName] = pin;
    }

}

Input *BaseNode::getInput(const QString &slotName)
{
    if(inputs.contains(slotName))
        return inputs[slotName];

    return nullptr;
}

Input *BaseNode::getInput(const QString &&slotName)
{
    if(inputs.contains(slotName))
        return inputs[slotName];

    return nullptr;
}

Output *BaseNode::getOutput(const QString &signalName)
{
    if(outputs.contains(signalName))
        return outputs[signalName];

    return nullptr;
}

Output *BaseNode::getOutput(const QString &&signalName)
{
    if(outputs.contains(signalName))
        return outputs[signalName];

    return nullptr;
}

DataPin *BaseNode::getPin(const QString &pinName)
{
    if(pins.contains(pinName))
        return pins[pinName];

    return nullptr;
}

DataPin *BaseNode::getPin(const QString &&pinName)
{
    return getPin(pinName);
}

void BaseNode::connectToViewer(const NodeView *viewer)
{
    for(auto i:inputs)
        connect(i, SIGNAL(receiveConnection(BaseNode*,QString)), viewer, SLOT(connectionEnds(BaseNode*,QString)));
    for(auto o:outputs)
        connect(o, SIGNAL(startConnection(BaseNode*,QString)), viewer, SLOT(connectionStarts(BaseNode*,QString)));
    for(auto p:pins)
        connect(p, SIGNAL(dataConnection(DataPin*)), viewer, SLOT(startConnectionData(DataPin*)));
    Movable::connectToViewer(viewer);
}

void BaseNode::disconnectFromViewer()
{
    for(auto i:inputs)
        disconnect(i, SIGNAL(receiveConnection(BaseNode*,QString)));
    for(auto o:outputs)
        disconnect(o, SIGNAL(startConnection(BaseNode*,QString)));
    for(auto p:pins)
        disconnect(p, SIGNAL(dataConnection(DataPin*)));
    Movable::disconnectFromViewer();
}

void BaseNode::inputConnected()
{
    inputCount++;
}

void BaseNode::inputDisconnected()
{
    inputCount--;
}

int BaseNode::type()
{
    return movableNode;
}


void BaseNode::paintEvent(QPaintEvent *pe)
{
    QPainter p(this);
    setUpStyle(p);
    p.end();

    Movable::paintEvent(pe);
}

void BaseNode::setUpStyle(QPainter &p)
{
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BaseNode::rearangeInputs()
{
    if(inputs.count() == 0)
        return;

    int perInputSpace = (height() - nameLab->height())/(inputs.count() + 1);
    int offset = nameLab->height();
    int xOff = pinSize.width() + 5;

    int i = 1;
    for(auto in:inputs)
    {
        int y = offset + (i++)*perInputSpace;
        in->move(0, y);
        in->getLab()->move(xOff, y - in->height()/2);
    }
}

void BaseNode::rearangeOutputs()
{
    if(outputs.count() == 0)
        return;

    int perOutputSpace = (height() - nameLab->height())/(outputs.count() + 1);
    int offset = nameLab->height();
    int x = width() - pinSize.width();

    int i = 1;
    for(auto out:outputs)
    {
        int y = offset + (i++)*perOutputSpace;
        out->move(x, y);
        out->getLab()->move(x - out->getLab()->width()/2, y - out->height()/2);
    }
}

void BaseNode::rearangePins()
{
    if(pins.count() == 0)
        return;

    int perPinSpace = (width()/(pins.count() + 1)) - pinSize.width()/2;
    int y = height() - pinSize.height();

    int i = 1;
    for(auto pin:pins)
    {
        int x = perPinSpace * (i++);
        pin->move(x, y);
    }
}

void BaseNode::becomeInactive()
{
    setObjectName("inactive");
    setStyleSheet(this->styleSheet());
}

void BaseNode::becomeActive()
{
    setObjectName("active");
    setStyleSheet(this->styleSheet());

    Movable::becomeActive();
}

void BaseNode::enable(BaseNode *)
{
#ifdef ENABLED_CHECK
    qDebug() << "enabled" << nodeName;
#endif
    emit done(this);
}
