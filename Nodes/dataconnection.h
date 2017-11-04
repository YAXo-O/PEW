#ifndef DATACONNECTION_H
#define DATACONNECTION_H

#include "datapin.h"
#include "nodedata.h"

class DataConnection
{
public:
    DataConnection(DataPin *pin = nullptr, NodeData *data = nullptr);

    DataPin *getPin() const;
    NodeData *getData() const;
    void setPin(DataPin *pin);
    void setData(NodeData *pin);

private:
    DataPin *pin;
    NodeData *data;
};

#endif // DATACONNECTION_H
