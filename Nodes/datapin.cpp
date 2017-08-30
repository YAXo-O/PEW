#include <QPainter>
#include "datapin.h"
#include "DataPinStates/readonlystate.h"
#include "DataPinStates/writeonlystate.h"
#include "DataPinStates/readwritestate.h"

DataPin::DataPin(const char *_type, dataFlowFlag direction, QWidget *parent) : QWidget(parent),
     type(_type), dir(direction), pinColour(200, 0, 200)
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
}

DataPin::~DataPin()
{
    if(state)
        delete state;
}

void DataPin::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    p.setPen(pinColour);
    p.setBrush(pinColour);

    state->paint(&p);

    p.end();
}
