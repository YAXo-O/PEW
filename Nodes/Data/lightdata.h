#ifndef LIGHTDATA_H
#define LIGHTDATA_H

#include "../../CompulsorySceneObjects/baselight.h"
#include "../nodedata.h"


class LightData : public NodeData
{
    Q_OBJECT
public:
    explicit LightData(QWidget *parent = nullptr);
    virtual ~LightData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

private:
    BaseLight *data;
};

#endif // LIGHTDATA_H
