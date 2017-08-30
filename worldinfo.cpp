#include "worldinfo.h"

WorldInfo::~WorldInfo()
{
    // Hopefully it works. Should remember not do add thier anything, that has to be deleted any other way
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
    nview = view;
}

NodeView *WorldInfo::getNodeView() const
{
    return nview;
}

WorldInfo::WorldInfo(): QObject(nullptr),
    currentFrame(0), startFrame(0), endFrame(100), fps(30),
    nview(nullptr), viewport(nullptr), nodeParams(nullptr)
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

void WorldInfo::registerObject(SceneObject *appendee)
{
    if(!appendee)
        return;

    // TODO: Do check? Lena approves
    for(auto i: objects)
        if(i == appendee)
            return;

    objects.append(appendee);
}

void WorldInfo::removeObject(SceneObject *removee)
{
    if(!removee)
        return;

    objects.removeOne(removee);
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
