#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QString>
#include <QMap>
#include <QImage>

class TextureManager
{
public:
    TextureManager() = default;
    ~TextureManager();

    QImage *getTexture(const QString &filename);
    QImage *getTexture(const QString &&filename);

private:
    QMap<QString, QImage *> table;
};

#endif // TEXTUREMANAGER_H
