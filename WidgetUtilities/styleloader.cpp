#include <QFile>
#include "styleloader.h"

StyleLoader::StyleLoader()
{
}

QString StyleLoader::loadCSS(const QString &fileName)
{
    QFile f(fileName);
    f.open(QFile::ReadOnly);
    if(f.error() != QFile::NoError)
        return "";

    return f.readAll();
}

QString StyleLoader::loadCSS(const QString &&fileName)
{
    return loadCSS(fileName);
}
