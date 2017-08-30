#include "colourfileparsing.h"

#include <QDebug>

ColourFileParsing::ColourFileParsing(const char *fileName): DataStorageParser(fileName)
{
    defaultActionsSetup();
}

ColourFileParsing::ColourFileParsing(const QString &fileName): DataStorageParser(fileName)
{
    defaultActionsSetup();
}

ColourFileParsing::ColourFileParsing(const QString &&fileName): DataStorageParser(fileName)
{
    defaultActionsSetup();
}

ColourFileParsing::~ColourFileParsing()
{
}

void ColourFileParsing::defaultActionsSetup()
{
    addAction(":", fpointer(&(ColourFileParsing::selectColour)));
}

bool ColourFileParsing::selectColour()
{
    if(currentPair.identifier == "")
    {

        errorRoutine("No identifier, but color value is expected");

        return false;
    }
    currentPair.value = "";
    for(int i = 0; i < 3; i++)
    {
        if(text.atEnd())
            return false;

        QString curWord;
        text >> curWord;
        double res;

        if(!getDouble(curWord, res))
            return false;
        else if(i != 3)
            currentPair.value += curWord + " ";
    }

    if(!pairHolder)
        pairHolder = new QHash<QString, QString>;
    if(pairHolder->contains(currentPair.identifier))
    {
            errorRoutine("identifier overwrite: " + currentPair.identifier);

            return false;
    }
    else
        pairHolder->operator[](currentPair.identifier) = currentPair.value;

    return true;
}
