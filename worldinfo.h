#ifndef WORLDINFO_H
#define WORLDINFO_H

#include <QObject>
#include <QImage>
#include <QList>
#include "nodeview.h"
#include "viewport.h"
#include "sceneobject.h"
#include "CompulsorySceneObjects/camera.h"

class NodeData;

class WorldInfo : public QObject
{
    Q_OBJECT

public:
    WorldInfo(const WorldInfo &other) = delete;
    ~WorldInfo();

    WorldInfo &operator=(const WorldInfo &other) = delete;

    static WorldInfo &getInstance();

    void setNodeView(NodeView *view);
    NodeView *getNodeView() const;

    void setViewport(Viewport *&viewport);
    Viewport *getViewport() const;

    void setNodeParams(PEWWidget *nodeParams);
    PEWWidget *getNodeParams() const;

    void registerObject(SceneObject *appendee);
    void removeObject(SceneObject *removee);
    void deleteObject(SceneObject *&deletee); // Delete - removes from list and frees memory

    QList<SceneObject *>::iterator begin();
    QList<SceneObject *>::iterator end();
    int objectsCount();

protected:
    WorldInfo();

private:
    // timing
    unsigned currentFrame;
    unsigned startFrame;
    unsigned endFrame;
    double fps;
    NodeView *nview;
    Viewport *viewport;
    PEWWidget *nodeParams;
    QList<SceneObject *> objects;

public slots:
    void changeCurrentFrame(unsigned newCF);
    void changeStartFrame(unsigned newSF);
    void changeEndFrame(unsigned newEF);
    void changeFPS(double newFPS);
    void renderFrame(QImage *&frame);

signals:
    void currentFrameChanged(unsigned newCF);
    void startFrameChanged(unsigned newSF);
    void endFrameChanged(unsigned newEF);
    void fpsChanged(double newFPS);
};

#endif // WORLDINFO_H
