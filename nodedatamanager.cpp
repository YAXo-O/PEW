#include "nodedatamanager.h"

void NodeDataManager::getInstance(NodeDataManager *&man, DataStorageParser *parser)
{
    static NodeDataManager *ndmanager = nullptr;

    if(!ndmanager && parser)
        ndmanager = new NodeDataManager(parser);

    man = ndmanager;
}

void NodeDataManager::resetTable(DataStorageParser *parser) throw(std::invalid_argument)
{
    if(dataTable)
        delete dataTable;

    if(parser)
        dataTable = parser->operator()();
    else
        throw std::invalid_argument("No parser is specified");
}

NodeDataManager::~NodeDataManager()
{
    if(dataTable)
        delete dataTable;
}

QString NodeDataManager::getValue(const QString &key) const throw(std::out_of_range)
{
    if(dataTable && dataTable->contains(key))
        return dataTable->value(key);
    else
        throw std::out_of_range("No value found for specific key in NodeDataManager table");
}

QString NodeDataManager::getValue(const QString &&key) const throw(std::out_of_range)
{
    return getValue(key);
}

NodeDataManager::NodeDataManager(DataStorageParser *parser) throw(std::invalid_argument) :
    dataTable((parser == nullptr) ? throw std::invalid_argument("No parser is specified") : parser->operator()())
{
}
