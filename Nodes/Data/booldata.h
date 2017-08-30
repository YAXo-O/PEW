#ifndef BOOLDATA_H
#define BOOLDATA_H

#include "../nodedata.h"

class BoolData : public NodeData
{
    Q_OBJECT
public:
    explicit BoolData(QWidget *parent = nullptr);
    virtual ~BoolData();

    const void *getData() const override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

private:
    bool data;
};

#endif // BOOLDATA_H
