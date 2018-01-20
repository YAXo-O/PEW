#ifndef CAMERADATA_H
#define CAMERADATA_H

#include "../nodedata.h"
#include "../../CompulsorySceneObjects/camera.h"

class CameraData : public NodeData
{
    Q_OBJECT
public:
    explicit CameraData(QWidget *parent = nullptr);
    virtual ~CameraData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

protected:
    void paintEvent(QPaintEvent *pe) override;

    void prepareParamPanel() override;

private:
    Camera *data;
};


#endif // CAMERADATA_H
