#ifndef COLOURFILEPARSING_H
#define COLOURFILEPARSING_H

#include "../datastorageparser.h"

class ColourFileParsing : public DataStorageParser
{
public:
    ColourFileParsing();
    ColourFileParsing(const char *fileName = nullptr);
    ColourFileParsing(const QString &fileName);
    ColourFileParsing(const QString &&fileName);
    virtual ~ColourFileParsing();

    void defaultActionsSetup() override;

private:
    bool selectColour();
};

#endif // COLOURFILEPARSING_H
