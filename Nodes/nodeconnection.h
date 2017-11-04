#ifndef NODECONNECTION_H
#define NODECONNECTION_H

#include <QObject>
#include "input.h"
#include "output.h"

class NodeConnection : public QObject
{
    Q_OBJECT
public:
    explicit NodeConnection(Output *start = nullptr, Input *end = nullptr, QObject *parent = nullptr);
    ~NodeConnection();

    Output *getStart() const;
    void setStart(Output *start);
    Input *getEnd() const;
    void setEnd(Input *value);

    bool hasFired() const;
    void resetFired();

private:
    Output *start;
    Input *end;
    bool bFired;

public slots:
    void fire(BaseNode *starter);

signals:
    void fired(BaseNode *starter);

};

#endif // NODECONNECTION_H
