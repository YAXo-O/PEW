#ifndef DATAPINSTATE_H
#define DATAPINSTATE_H

#include <QWidget>

class DataPin;

class DataPinState
{
public:
    explicit DataPinState(DataPin *parent = nullptr);
    virtual ~DataPinState();

    virtual void paint(QPainter *p) = 0;

    void setColour(const QColor &colour);
    void setColour(const QColor &&colour);
    QColor getColour() const;

    virtual const void *readValue();
    virtual void writeValue(void *value);

protected:
    DataPin *getParent() const;

private:
    DataPin *parent;
    QColor drawColor;
};

#endif // DATAPINSTATE_H
