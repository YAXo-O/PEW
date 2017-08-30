#ifndef READWRITESTATE_H
#define READWRITESTATE_H

#include "datapinstate.h"

class ReadWriteState : public DataPinState
{
public:
    explicit ReadWriteState(QWidget *parent = nullptr);
    ~ReadWriteState();

    void paint(QPainter *p) override;
};

#endif // READWRITESTATE_H
