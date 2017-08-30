#ifndef NODEDATAMANAGER_H
#define NODEDATAMANAGER_H

#include <QHash>
#include "WidgetUtilities/datastorageparser.h"

const QString configPath = "config/";

// Add path getter class

class NodeDataManager
{
public:
    static void getInstance(NodeDataManager *&man, DataStorageParser *parser);
    void resetTable(DataStorageParser *parser) throw(std::invalid_argument);

    virtual ~NodeDataManager();

protected:
    QString getValue(const QString &key) const throw(std::out_of_range);
    QString getValue(const QString &&key) const throw(std::out_of_range);

    NodeDataManager(DataStorageParser *parser) throw(std::invalid_argument);

private:
    // Data nodes info
    QHash<QString, QString> *dataTable;

};

#endif // NODEDATAMANAGER_H
