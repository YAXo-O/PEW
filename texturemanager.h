#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

template<typename T1, typename T2>
class QMap;
class QString;
class QImage;

class TextureManager
{
public:
    TextureManager() = default;
    ~TextureManager();

    QImage &getTexture(const QString &filename);
    QImage &getTexture(const QString &&filename);

private:
    QMap<QString, QImage *> table;
};

#endif // TEXTUREMANAGER_H
