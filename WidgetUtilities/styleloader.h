#ifndef STYLELOADER_H
#define STYLELOADER_H

#include <QString>

const QString cssPath = "css/";

class StyleLoader
{
public:
    StyleLoader();

    static QString loadCSS(const QString &fileName);
    static QString loadCSS(const QString &&fileName);
};

#endif // STYLELOADER_H
