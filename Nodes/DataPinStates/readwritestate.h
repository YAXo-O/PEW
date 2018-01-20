#ifndef READWRITESTATE_H
#define READWRITESTATE_H

#include "datapinstate.h"

class ReadWriteState : public DataPinState
{
public:
    explicit ReadWriteState(DataPin *parent = nullptr);
    ~ReadWriteState();

    const void *readValue() override;
    void writeValue(void *value) override;

    void paint(QPainter *p) override;
};

#endif // READWRITESTATE_H
