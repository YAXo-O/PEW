#include "../datapin.h"
#include "datapinstate.h"
#include "../pinproperties.h"

DataPinState::DataPinState(DataPin *_parent): parent(_parent)
{
    parent->resize(pinSize);
}

DataPinState::~DataPinState()
{
}

DataPin *DataPinState::getParent() const
{
    return parent;
}

void DataPinState::setColour(const QColor &colour)
{
    drawColor = colour;
}

void DataPinState::setColour(const QColor &&colour)
{
    drawColor = colour;
}

QColor DataPinState::getColour() const
{
    return drawColor;
}

const void *DataPinState::readValue()
{
    return nullptr;
}

void DataPinState::writeValue(void *)
{
}
