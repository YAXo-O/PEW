#ifndef INTDATA_H
#define INTDATA_H

#include <stddef.h>
#include "../nodedata.h"
#include "./intdatawidget.h"

class IntData : public NodeData
{
    Q_OBJECT
public:
    explicit IntData(QWidget *parent = nullptr);
    virtual ~IntData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

private:
    int32_t data;
    IntDataWidget wid;
};

#endif // INTDATA_H
