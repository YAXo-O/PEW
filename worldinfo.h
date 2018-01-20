#ifndef WORLDINFO_H
#define WORLDINFO_H

#include <QObject>
#include <QImage>
#include <QList>
#include "nodeview.h"
#include "viewport.h"
#include "sceneobject.h"
#include "CompulsorySceneObjects/camera.h"
#include "tracinginfo.h"
#include "CompulsorySceneObjects/baselight.h"
#include "texturemanager.h"

class NodeData;
class QVector3D;

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

    QList<BaseLight *>::iterator beginLights();
    QList<BaseLight *>::iterator endLights();
    int lightsCount();

    bool isBlocked(const QVector3D &origin,const QVector3D &dir);
    bool isBlocked(const QVector3D &origin, const QVector3D &dir, const QVector3D &exclude);
    TextureManager &textureManager();

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
    QList<BaseLight *> lights;
    TextureManager *tManager;

public slots:
    void changeCurrentFrame(unsigned newCF);
    void changeStartFrame(unsigned newSF);
    void changeEndFrame(unsigned newEF);
    void changeFPS(double newFPS);
    void renderFrame(QImage *&frame);
    void simulate();

signals:
    void currentFrameChanged(unsigned newCF);
    void startFrameChanged(unsigned newSF);
    void endFrameChanged(unsigned newEF);
    void fpsChanged(double newFPS);
    void resetSimulation();
};

#endif // WORLDINFO_H
