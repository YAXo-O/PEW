#ifndef WRITEONLYSTATE_H
#define WRITEONLYSTATE_H

#include "datapinstate.h"

class WriteOnlyState : public DataPinState
{
public:
    explicit WriteOnlyState(DataPin *parent = nullptr);
    virtual ~WriteOnlyState();

    const void *readValue() override;
    void writeValue(void *value) override;

    virtual void paint(QPainter *p);
};

#endif // WRITEONLYSTATE_H
