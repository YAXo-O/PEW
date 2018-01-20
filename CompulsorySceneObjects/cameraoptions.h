#ifndef CAMERAOPTIONS_H
#define CAMERAOPTIONS_H

#include <QVector3D>

struct cameraOptions
{
    int roll = 0;
    int pitch = 0;
    int yaw = 0;
    QVector3D location;
    float fov;
};

#endif // CAMERAOPTIONS_H
