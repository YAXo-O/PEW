#ifndef MODELINFO_H
#define MODELINFO_H

#include <QVector3D>
#include <QColor>
#include <QVector>

struct face
{
    QVector<size_t> verts;
    QVector<size_t> normals;
    QVector<size_t> uvs;

    QColor color = Qt::red; // Пока сделаем грани, закрашенные одним цветом
    bool bVisible = true;
};

#endif // MODELINFO_H
