#include <QMap>
#include <QString>
#include <QImage>
#include <QFile>

#include "texturemanager.h"

TextureManager::~TextureManager()
{
    for(auto i : table)
        delete i;
}

QImage *TextureManager::getTexture(const QString &filename)
{
    if(table.contains(filename))
        return table[filename];

    table[filename] = new QImage(filename);

    return table[filename];
}

QImage *TextureManager::getTexture(const QString &&filename)
{
    return getTexture(filename);
}
