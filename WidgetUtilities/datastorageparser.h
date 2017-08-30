#ifndef DATASTORAGEPARSER_H
#define DATASTORAGEPARSER_H

#include <QFile>
#include <QString>
#include <QHash>
#include <QTextStream>

class DataStorageParser;
typedef bool (DataStorageParser:: *fpointer)();

struct pair
{
    QString identifier, value;
};

class DataStorageParser
{
public:
    DataStorageParser(const char *fileName = nullptr);
    DataStorageParser(const QString &fileName);
    DataStorageParser(const QString &&fileName);
    virtual ~DataStorageParser();

    void setFile(const char *fileName = nullptr);
    void setFile(const QString &fileName);
    void setFile(const QString &&fileName);
    QString getFile() const;

    void addAction(const QString &keyword, fpointer action);
    void addAction(const QString &&keyword, fpointer action);
    void removeAction(const QString &keyword);
    void removeAction(const QString &&keyword);

    virtual QHash<QString, QString> *operator()(); // Parses current file
    virtual void defaultActionsSetup(); // Sets up default actions (comments)

    void setShowError(bool bShow);
    bool showError();

protected:
    QFile *file;
    QTextStream text;
    pair currentPair;
    QHash<QString, QString> *pairHolder;

    bool getDouble(QString number, double &result); // Returns value of number if given word is a number
    bool isId(const QString &word); // Checks if current word is identifier
    bool isId(const QString &&word);
    bool getKeyWord(const QString &word, fpointer &action); // Checks if current word is a keyword
    bool getKeyWord(const QString &&word, fpointer &action);

    void errorRoutine(QString errorDetails = ""); // Is called when error is occured

private:
    QHash<QString, fpointer> keywords; // Hash of keywords and its actions
    bool bShowError; // Show error message?

    // Actions
    bool singleLineComment(); // Action for a single-line comment (skips one line)
    bool multiLineComment(); // Action for multi-line comments (skips everything till the next comment keyword)
};

#endif // DATASTORAGEPARSER_H
