#ifndef NODEPARAMSCONTAINER_H
#define NODEPARAMSCONTAINER_H

#include <QWidget>

class NodeParamsContainer
{
public:
    NodeParamsContainer(QWidget *paramsPanel);

    QWidget *getParamsPanel() const;

    virtual const void *getValue();

private:
    QWidget *panel;
};

#endif // NODEPARAMSCONTAINER_H
