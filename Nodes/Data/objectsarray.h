#ifndef OBJECTSARRAY_H
#define OBJECTSARRAY_H

#include <QVector>
#include "../basenode.h"

class SceneObject;

class ObjectsArray : public NodeData
{
    Q_OBJECT
public:
    explicit ObjectsArray(QWidget *parent = nullptr);
    virtual ~ObjectsArray() {}

    bool isPresent() const override;
    const void *getData() override;
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

private:
    QVector<SceneObject *> *array;

};

#endif // OBJECTSARRAY_H
