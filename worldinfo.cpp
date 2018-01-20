#include "worldinfo.h"

WorldInfo::~WorldInfo()
{
    // Hopefully it works. Should remember not do add there anything, that has to be deleted any other way
    // Or maybe using smart pointers?
    for(auto i: objects)
        delete i;
}

WorldInfo &WorldInfo::getInstance()
{
    static WorldInfo instance;

    return instance;
}

void WorldInfo::setNodeView(NodeView *view)
{
    if(nview)
        disconnect(this, SIGNAL(resetSimulation()), nview, SIGNAL(resetMovables()));
    nview = view;
    connect(this, SIGNAL(resetSimulation()), view, SIGNAL(resetMovables()));
}

NodeView *WorldInfo::getNodeView() const
{
    return nview;
}

WorldInfo::WorldInfo(): QObject(nullptr),
    currentFrame(0), startFrame(0), endFrame(100), fps(30),
    nview(nullptr), viewport(nullptr), nodeParams(nullptr), tManager(new TextureManager)
{
}

Viewport *WorldInfo::getViewport() const
{
    return viewport;
}

void WorldInfo::setNodeParams(PEWWidget *_nodeParams)
{
    nodeParams = _nodeParams;
}

PEWWidget *WorldInfo::getNodeParams() const
{
    return nodeParams;
}

RenderStatus &WorldInfo::getRenderStatus()
{
    return stat;
}

void WorldInfo::registerObject(SceneObject *appendee)
{
    if(!appendee)
        return;

    // TODO: Do check? Lena approves
    for(auto i: objects)
        if(i == appendee)
            return;

    objects.append(appendee);
    if(appendee->type() == BaseLight::type_s())
        lights.append(dynamic_cast<BaseLight *>(appendee));
}

void WorldInfo::removeObject(SceneObject *removee)
{
    if(!removee)
        return;

    objects.removeOne(removee);
    if(removee->type() == BaseLight::type_s())
        lights.removeOne(dynamic_cast<BaseLight*>(removee));
}

void WorldInfo::deleteObject(SceneObject *&deletee)
{
    if(deletee)
    {
        removeObject(deletee);
        delete deletee;
        deletee = nullptr;
    }
}

QList<SceneObject *>::iterator WorldInfo::begin()
{
    return objects.begin();
}

QList<SceneObject *>::iterator WorldInfo::end()
{
    return objects.end();
}

int WorldInfo::objectsCount()
{
    return objects.count();
}

QList<BaseLight *>::iterator WorldInfo::beginLights()
{
    return lights.begin();
}

QList<BaseLight *>::iterator WorldInfo::endLights()
{
    return lights.end();
}

int WorldInfo::lightsCount()
{
    return lights.count();
}

bool WorldInfo::isBlocked(const QVector3D &origin, const QVector3D &dir)
{
    for(auto i = begin(); i != end(); i++)
    {
        if((*i)->blocks(origin, dir))
            return true;
    }

    return false;
}

bool WorldInfo::isBlocked(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude)
{
    for(auto i = begin(); i != end(); i++)
    {
        if((*i)->blocks(origin, dir, exclude))
            return true;
    }

    return false;
}

TextureManager &WorldInfo::textureManager()
{
    return *tManager;
}

unsigned WorldInfo::getCurrentFrame() const
{
    return currentFrame;
}

void WorldInfo::setViewport(Viewport *&value)
{
    viewport = value;
}

void WorldInfo::changeCurrentFrame(unsigned newCF)
{
    currentFrame = newCF;

    emit currentFrameChanged(newCF);
}

void WorldInfo::changeStartFrame(unsigned newSF)
{
    startFrame = newSF;

    emit startFrameChanged(newSF);
}

void WorldInfo::changeEndFrame(unsigned newEF)
{
    endFrame = newEF;

    emit endFrameChanged(newEF);
}

void WorldInfo::changeFPS(double newFPS)
{
    fps = newFPS;

    emit fpsChanged(newFPS);
}

void WorldInfo::renderFrame(QImage *&frame)
{
    frame = nullptr;
    if(nview)
        nview->getBuffer(frame);
}

void WorldInfo::simulate()
{
    emit resetSimulation();
    nview->simulate();
}
