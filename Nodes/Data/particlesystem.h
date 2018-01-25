#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QVector>
#include "../basenode.h"
#include "../../particle.h"

class ParticleSystem : public NodeData
{
    Q_OBJECT
public:
    explicit ParticleSystem(QWidget *parent = nullptr);
    virtual ~ParticleSystem();

    bool isPresent() const override;
    const void *getData();
    void setData(const void *newData) override;
    const char *dataType() const override;
    static const char *dataType_s();

public slots:
    void resetMovable() override;

private:
    QVector<Particle *> *system;

};

#endif // PARTICLESYSTEM_H
