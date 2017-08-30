#ifndef WRITEONLYSTATE_H
#define WRITEONLYSTATE_H

#include "datapinstate.h"

class WriteOnlyState : public DataPinState
{
public:
    explicit WriteOnlyState(QWidget *parent = nullptr);
    virtual ~WriteOnlyState();

    virtual void paint(QPainter *p);
};

#endif // WRITEONLYSTATE_H
