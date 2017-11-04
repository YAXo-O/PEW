#ifndef DATAPIN_H
#define DATAPIN_H

#include <QWidget>
#include "DataPinStates/datapinstate.h"
#include "nodedata.h"

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
    explicit DataPin(const QString &name = "Unnamed", const char *type = nullptr, dataFlowFlag direction = DFF_READ,
                      QWidget *parent = nullptr);
    explicit DataPin(const QString &&name, const char *type = nullptr, dataFlowFlag direction = DFF_READ,
                     QWidget *parent = nullptr);
    ~DataPin();

    void setConnections();
    void breakConnections();

    void *readValue();
    void writeValue(void *value);

    NodeData *getData() const;
    void setData(NodeData *data);

    const char *getType();

    const QString &getName() const;
    void setName(const QString &name);
    void setName(const QString &&name);

    const QColor &getColor() const;

protected:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *me) override;

private:
    QString name;
    const char *type;
    dataFlowFlag dir;
    DataPinState *state;
    QColor pinColour;
    NodeData *data;

signals:
    void dataConnection(DataPin *emitter);
};

#endif // DATAPIN_H
