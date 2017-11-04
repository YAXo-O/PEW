#include "datapinstate.h"
#include "../pinproperties.h"

DataPinState::DataPinState(QWidget *_parent): parent(_parent)
{
    parent->resize(pinSize);
}

DataPinState::~DataPinState()
{
}

QWidget *DataPinState::getParent() const
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

void *DataPinState::readValue()
{
    return nullptr;
}

void DataPinState::writeValue(void *)
{
}
