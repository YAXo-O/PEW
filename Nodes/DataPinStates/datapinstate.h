#ifndef DATAPINSTATE_H
#define DATAPINSTATE_H

#include <QWidget>

class DataPinState
{
public:
    explicit DataPinState(QWidget *parent = nullptr);
    virtual ~DataPinState();

    virtual void paint(QPainter *p) = 0;

    QWidget *getParent() const;

    void setColour(const QColor &colour);
    void setColour(const QColor &&colour);
    QColor getColour() const;

private:
    QWidget *parent;
    QColor drawColor;
};

#endif // DATAPINSTATE_H
