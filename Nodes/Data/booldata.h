#ifndef BOOLDATA_H
#define BOOLDATA_H

#include "../nodedata.h"
#include "booldatawidget.h"

class BoolData : public NodeData
{
    Q_OBJECT
public:
    explicit BoolData(QWidget *parent = nullptr);
    virtual ~BoolData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

protected:
    void paintEvent(QPaintEvent *pe) override;

    void prepareParamPanel() override;

private:
    BoolDataWidget *dataWidget;
    bool data;
};

#endif // BOOLDATA_H
