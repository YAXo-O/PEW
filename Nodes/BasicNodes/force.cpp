#include "force.h"
#include "../externalvariablefactory.h"
#include "../Data/particlesystem.h"
#include "../../particle.h"
#include "../../worldinfo.h"

Force::Force(QString name, QWidget *parent): BaseNode(name, parent)
{
    system = ExternalVariableFactory::createExternal(ParticleSystem::dataType_s(), "Particle System", DFF_BOTH);

    addDataPin(system->getPin());

    rearangePins();
}

void Force::enable(BaseNode *caller)
{
    if(system->isDataPresent())
    {
        WorldInfo &info = WorldInfo::getInstance();
        QVector<Particle *> *ps = (QVector<Particle *> *)system->getValue();
        unsigned frame = info.getCurrentFrame();
        int timeFactor = 2*frame - 1;

        for(int i = 0; i < ps->count(); i++)
        {
            if(ps->at(i)->checkAttribute("acc"))
            {
                QVector3D offset = *((QVector3D *)(ps->at(i)->getAttribute("acc")));

                ps->at(i)->getModel->move({offset.x()/2*timeFactor, offset.y()/2*timeFactor, offset.z()/2*timeFactor});
            }
            else
            {
                ps->at(i)->addAttribute("acc", new QVector3D(0, 0, -10));
            }
        }
    }

    BaseNode::enable(caller);
}
