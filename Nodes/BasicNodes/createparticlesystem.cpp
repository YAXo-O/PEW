#include <QVector3D>

#include "createparticlesystem.h"
#include "../externalvariablefactory.h"
#include "../Data/objectsarray.h"
#include "../Data/particlesystem.h"
#include "../../sceneobject.h"
#include "../../worldinfo.h"

CreateParticleSystem::CreateParticleSystem(QString nodeName, QWidget *parent): BaseNode(nodeName, parent),
    wid(new CreateParticleSystemContainer(new CreateParticleSystemWidget))
{
    array = ExternalVariableFactory::createExternal(ObjectsArray::dataType_s(), "Reference models", DFF_BOTH);
    particleSystem = ExternalVariableFactory::createExternal(ParticleSystem::dataType_s(), "Particle System", DFF_BOTH);

    addDataPin(array->getPin());
    addDataPin(particleSystem->getPin());

    rearangePins();
    appendParamsWidget(wid->getParamsPanel());
}

void CreateParticleSystem::enable(BaseNode *caller)
{
    psCreate data = *(psCreate *)(wid->getValue());

    if(array->isDataPresent())
    {
        QVector<SceneObject *> *vector = (QVector<SceneObject *> *)(array->getValue());
        for(int i = 0; i < vector->size(); i++)
            vector->at(i)->setVisible(false);

        int variant = vector->size() - 1;
        if(particleSystem->isConnected())
        {
            QVector<Particle *> *ps = (QVector<Particle *> *)(particleSystem->getValue());

            static std::mt19937_64 generator;
            std::uniform_real_distribution<double> radiusD(-data.rad, data.rad);
            std::uniform_int_distribution<unsigned> shapeD(0, variant);
            std::uniform_real_distribution<double> dirD(-1, 1);

            for(int i = 0; i < data.count; i++)
            {
                SceneObject *m = vector->at(shapeD(generator))->copy();
                QVector3D pos = {dirD(generator), dirD(generator), dirD(generator)};
                m->moveTo(data.pos + pos*radiusD(generator));
                m->setVisible(true);

                Particle *p = new Particle(m);
                unsigned *birth = new unsigned;
                *birth = WorldInfo::getInstance().getCurrentFrame();
                p->addAttribute("birth", birth);

                ps->append(p);

            }

        }
    }

    BaseNode::enable(caller);
}
