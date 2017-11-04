#include "nodeconnection.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

#define NO_CONNECTION_CHECK

NodeConnection::NodeConnection(Output *_start, Input *_end, QObject *parent): QObject(parent),
    start(_start), end(_end), bFired(false)
{
}

NodeConnection::~NodeConnection()
{
    disconnect(this, SIGNAL(fired(BaseNode*)));
    disconnect(this, SLOT(fire(BaseNode*)));
}

Output *NodeConnection::getStart() const
{
    return start;
}

void NodeConnection::setStart(Output *_start)
{
    start = _start;
}

Input *NodeConnection::getEnd() const
{
    return end;
}

void NodeConnection::setEnd(Input *_end)
{
    end = _end;
}

bool NodeConnection::hasFired() const
{
    return bFired;
}

void NodeConnection::resetFired()
{
    bFired = false;
}

void NodeConnection::fire(BaseNode *starter)
{
    bFired = true;

    emit fired(starter);
#if defined(DEBUG) && defined(CONNECTION_CHECK)
    qDebug() << "Connection fired";
#endif
}
