#ifndef COLORDATA_H
#define COLORDATA_H

#include "../nodedata.h"
#include "./colordatawidget.h"

class ColorData : public NodeData
{
    Q_OBJECT
public:
    explicit ColorData(QWidget *parent = nullptr);
    virtual ~ColorData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

private:
    QColor data;
    ColorDataWidget wid;

    void debugColor(const QColor &value);
};

#endif // COLORDATA_H
