#ifndef WIREFRAMEMESHINSTANCEDATA_H
#define WIREFRAMEMESHINSTANCEDATA_H

#include "../../Model/wireframemeshinstance.h"
#include "../nodedata.h"

class WireframeMeshInstanceData : public NodeData
{
public:
    explicit WireframeMeshInstanceData(QWidget *parent = nullptr);
    virtual ~WireframeMeshInstanceData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

private:
    WireframeMeshInstance *data;
};

#endif // WIREFRAMEMESHINSTANCEDATA_H
