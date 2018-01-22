#ifndef VECTORPARAMSCONTAINER_H
#define VECTORPARAMSCONTAINER_H

#include <QVector3D>
#include "../nodeparamscontainer.h"
#include "./vectordatawidget.h"

class VectorParamsContainer : public NodeParamsContainer
{
public:
    VectorParamsContainer(VectorDataWidget *paramsContainer);

    const void *getValue() override;

private:
    QVector3D data;
};

#endif // VECTORPARAMSCONTAINER_H
