#ifndef VECTORDATA_H
#define VECTORDATA_H

#include <QVector3D>

#include "../nodedata.h"
#include "./vectordatawidget.h"

class VectorData : public NodeData
{
    Q_OBJECT
public:
    explicit VectorData(QWidget *parent = nullptr);
    virtual ~VectorData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

private:
    QVector3D data;
    VectorDataWidget wid;

    void debugVector(const QVector3D &value);
};

#endif // VECTORDATA_H
