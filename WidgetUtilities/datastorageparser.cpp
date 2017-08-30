#include <QTextStream>
#include <cctype>
#include <QMessageBox>
#include "datastorageparser.h"

#define DEBUG
#ifdef DEBUG
#include <QDebug>
#endif

DataStorageParser::DataStorageParser(const char *fileName): file(nullptr), pairHolder(nullptr), bShowError(true)
{
    defaultActionsSetup();
    if(fileName && QFile::exists(fileName))
        file = new QFile(fileName);
}

DataStorageParser::DataStorageParser(const QString &fileName): file(nullptr), pairHolder(nullptr), bShowError(true)
{
    defaultActionsSetup();
    if(QFile::exists(fileName))
        file = new QFile(fileName);
}

DataStorageParser::DataStorageParser(const QString &&fileName): file(nullptr), pairHolder(nullptr), bShowError(true)
{
    defaultActionsSetup();
    if(QFile::exists(fileName))
        file = new QFile(fileName);
}

DataStorageParser::~DataStorageParser()
{
    if(file)
        delete file;

    if(pairHolder)
        delete pairHolder;
}

void DataStorageParser::setFile(const char *fileName)
{
    if(file)
        delete file;

    if(QFile::exists(fileName))
        file = new QFile(fileName);
    else
        file = nullptr;
}

void DataStorageParser::setFile(const QString &fileName)
{
    if(file)
        delete file;

    if(QFile::exists(fileName))
        file = new QFile(fileName);
    else
        file = nullptr;
}

void DataStorageParser::setFile(const QString &&fileName)
{
    if(file)
        delete file;

    if(QFile::exists(fileName))
        file = new QFile(fileName);
    else
        file = nullptr;
}

QString DataStorageParser::getFile() const
{
    return file ? file->fileName() : "";
}

void DataStorageParser::addAction(const QString &keyword, fpointer action)
{
    if(keywords.contains(keyword))
        return;
    else
        keywords[keyword] = action;
}

void DataStorageParser::addAction(const QString &&keyword, fpointer action)
{
    addAction(keyword, action);
}

void DataStorageParser::removeAction(const QString &keyword)
{
    keywords.remove(keyword);
}

void DataStorageParser::removeAction(const QString &&keyword)
{
    keywords.remove(keyword);
}

QHash<QString, QString> *DataStorageParser::operator()()
{
    if(pairHolder)
    {
        // If present, should clear it and start from scratch
        // Maybe it makes sense not to remove it all, but to append?
        delete pairHolder;
        pairHolder = new QHash<QString, QString>;
    }

    if(file && file->open(QIODevice::ReadOnly))
    {
        text.setDevice(file);
        QString curWord;
        while((text >> curWord), !text.atEnd())
        {
            fpointer action = nullptr;
            if(getKeyWord(curWord, action))
            {
                if(!(this->*action)())
                {
                    errorRoutine("Last read word: " + curWord);

                    return nullptr;
                }
            }
            else if(isId(curWord))
            {
                currentPair.identifier = curWord;
            }
            else
            {
                errorRoutine("Last read word: " + curWord);

                return nullptr;
            }

        }
        file->close();
    }
    QHash<QString, QString> *returnValue = pairHolder;
    pairHolder = nullptr;

    return returnValue;
}

void DataStorageParser::defaultActionsSetup()
{
    addAction(";", &DataStorageParser::singleLineComment);
    addAction("#", &DataStorageParser::multiLineComment);
}

void DataStorageParser::setShowError(bool bShow)
{
    bShowError = bShow;
}

bool DataStorageParser::showError()
{
    return bShowError;
}

bool DataStorageParser::getDouble(QString number, double &result)
{
    bool returnValue = false;
    result = number.toDouble(&returnValue);

    return returnValue;
}

bool DataStorageParser::isId(const QString &word)
{
    if(!isalpha((word[0]).toLatin1()) && word[0] != '_')
        return false;

    for(int i = 1; i < word.count(); i++)
        if(!isalnum(word[i].toLatin1()) && word[i] != '_')
            return false;

    return true;
}

bool DataStorageParser::isId(const QString &&word)
{
    return isId(word);
}

bool DataStorageParser::getKeyWord(const QString &word, fpointer &action)
{
    action = nullptr;

    for(auto i: keywords.keys())
    {
        if( i == word)
        {
            action = keywords[i];

            return true;
        }
    }

    return false;
}

bool DataStorageParser::getKeyWord(const QString &&word, fpointer &action)
{
    return getKeyWord(word, action);
}

void DataStorageParser::errorRoutine(QString errorDetails)
{
    if(file && file->isOpen())
        file->close();

    if(pairHolder)
    {
        delete pairHolder;
        pairHolder = nullptr;
    }

    if(bShowError)
    {
        QMessageBox msg;
        msg.setText("Error occured while file parsing;\n "
                    "Check input file for errors;");
        msg.setIcon(QMessageBox::Warning);
        if(errorDetails != "")
            msg.setInformativeText(errorDetails);
        msg.setWindowTitle("File parsing error!");
        msg.exec();
    }
}

bool DataStorageParser::singleLineComment()
{
    text.readLine();
    return true;
}

bool DataStorageParser::multiLineComment()
{
    char tmp = '\0' ;
    while(text >> tmp, (tmp != '#'))
        if(text.atEnd())
            return false;

    text.readLine();

    return true;
}
