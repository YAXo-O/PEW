#ifndef DATAPIN_H
#define DATAPIN_H

#include <QWidget>
#include "DataPinStates/datapinstate.h"

enum dataFlowFlag
{
    DFF_READ,
    DFF_WRITE,
    DFF_BOTH
};

class DataPin : public QWidget
{
    Q_OBJECT
public:
    explicit DataPin(const char *type, dataFlowFlag direction = DFF_READ, QWidget *parent = nullptr);
    ~DataPin();

protected:
    void paintEvent(QPaintEvent *pe) override;

private:
    const char *type;
    dataFlowFlag dir;
    DataPinState *state;
    QColor pinColour;
};

#endif // DATAPIN_H
