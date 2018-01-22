#ifndef FLOATDATA_H
#define FLOATDATA_H

#include "../nodedata.h"
#include "floatdatawidget.h"

class FloatData : public NodeData
{
    Q_OBJECT
public:
    explicit FloatData(QWidget *parent = nullptr);
    virtual ~FloatData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

    void prepareParamPanel() override;

private:
    double data;
    FloatDataWidget wid;
};

#endif // FLOATDATA_H
