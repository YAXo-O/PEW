#ifndef SCENEOBJECTDATA_H
#define SCENEOBJECTDATA_H

#include "../nodedata.h"
#include "../../sceneobject.h"

class SceneObjectData : public NodeData
{
    Q_OBJECT
public:
    explicit SceneObjectData(QWidget *parent = nullptr);
    virtual ~SceneObjectData();

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

private:
    SceneObject *data;
};

#endif // SCENEOBJECTDATA_H
