#ifndef MESHMANAGER_H
#define MESHMANAGER_H


template<typename T1, typename T2>
class QMap;
class QString;
class WireframeMesh;

class MeshManager
{
public:
    MeshManager() = default;
    ~MeshManager() = default;

    WireframeMesh *getMesh(const QString &filename);
    WireframeMesh *getMesh(const QString &&filename);

private:
    QMap<QString, WireframeMesh *> table;
};

#endif // MESHMANAGER_H
