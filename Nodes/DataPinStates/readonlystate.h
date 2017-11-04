#ifndef READONLYSTATE_H
#define READONLYSTATE_H

#include "datapinstate.h"

class ReadOnlyState : public DataPinState
{
public:
    explicit ReadOnlyState(QWidget *parent = nullptr);
    ~ReadOnlyState();

    //void *readValue() override;
    //void writeValue(void *value) override;

    void paint(QPainter *p) override;
};

#endif // READONLYSTATE_H
