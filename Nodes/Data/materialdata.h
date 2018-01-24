#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include "../nodedata.h"
#include "../../Model/material.h"

class MaterialData : public NodeData
{
    Q_OBJECT
public:
    explicit MaterialData(QWidget *parent = nullptr);
    virtual ~MaterialData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

private:
    Material *data;

};

#endif // MATERIALDATA_H
