#include "dataconnection.h"

DataConnection::DataConnection(DataPin *_pin, NodeData *_data): pin(_pin), data(_data)
{
}

DataPin *DataConnection::getPin() const
{
    return pin;
}


NodeData *DataConnection::getData() const
{
    return data;
}

void DataConnection::setPin(DataPin *_pin)
{
    pin = _pin;
}

void DataConnection::setData(NodeData *_data)
{
    data = _data;
}
