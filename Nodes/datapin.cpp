#include <QPainter>
#include "datapin.h"
#include "DataPinStates/readonlystate.h"
#include "DataPinStates/writeonlystate.h"
#include "DataPinStates/readwritestate.h"
#include "../worldinfo.h"
#include "../nodeview.h"

#include <QDebug>

DataPin::DataPin(const QString &_name, const char *_type, dataFlowFlag direction, QWidget *parent) : QWidget(parent),
     name(_name), type(_type), dir(direction), pinColour(200, 0, 200), data(nullptr)
{
    switch(dir)
    {
    case DFF_READ:
        state = new ReadOnlyState(this);
        break;

    case DFF_WRITE:
        state = new WriteOnlyState(this);
        break;

    case DFF_BOTH:
        state = new ReadWriteState(this);
        break;

    default:
        state = nullptr;
        break;
    }

    setToolTip(_name);
    setConnections();
}

DataPin::DataPin(const QString &&_name, const char *_type, dataFlowFlag direction, QWidget *parent) : QWidget(parent),
     name(_name), type(_type), dir(direction), pinColour(200, 0, 200), data(nullptr)
{
    switch(dir)
    {
    case DFF_READ:
        state = new ReadOnlyState(this);
        break;

    case DFF_WRITE:
        state = new WriteOnlyState(this);
        break;

    case DFF_BOTH:
        state = new ReadWriteState(this);
        break;

    default:
        state = nullptr;
        break;
    }

    setConnections();
}

DataPin::~DataPin()
{
    if(state)
        delete state;
    breakConnections();
}

void DataPin::setConnections()
{
    NodeView *view = WorldInfo::getInstance().getNodeView();
    if(view)
        connect(this, SIGNAL(dataConnection(DataPin*)), view, SLOT(startConnectionData(DataPin*)));
}

void DataPin::breakConnections()
{
    NodeView *view = WorldInfo::getInstance().getNodeView();
    if(view)
        disconnect(this, SIGNAL(dataConnection(DataPin*)));
}

const void *DataPin::readValue()
{
    return state->readValue();
}

void DataPin::writeValue(void *value)
{
    state->writeValue(value);
}

bool DataPin::isConnected() const
{
    return data != nullptr;
}

bool DataPin::isDataPresent() const
{
    return data != nullptr && data->isPresent();
}

void DataPin::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setPen(pinColour);
    p.setBrush(pinColour);

    state->paint(&p);

    p.end();
}

void DataPin::mousePressEvent(QMouseEvent *me)
{
    if(me->button() & Qt::LeftButton && me->modifiers() == 0 && !data)
        emit dataConnection(this);

    QWidget::mouseMoveEvent(me);
}

void DataPin::nodeKilled(Movable *node)
{
    data = nullptr;
    delete node;
}

NodeData *DataPin::getData() const
{
    return data;
}

void DataPin::setData(NodeData *_data)
{
    data = _data;
    if(data)
        connect(data, SIGNAL(killMe(Movable*)), this, SLOT(nodeKilled(Movable*)));
}

const char *DataPin::getType()
{
    return type;
}

const QString &DataPin::getName() const
{
    return name;
}

void DataPin::setName(const QString &_name)
{
    name = _name;
    setToolTip(name);
}

void DataPin::setName(const QString &&_name)
{
    name = _name;
}

const QColor &DataPin::getColor() const
{
    return pinColour;
}
