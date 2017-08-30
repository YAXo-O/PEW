#ifndef NODECOLOURMANAGER_H
#define NODECOLOURMANAGER_H

#include "../nodedatamanager.h"

class NodeData;

class NodeColourManager : public NodeDataManager
{
public:
    NodeColourManager(const NodeColourManager &other) = delete;
    NodeColourManager(const NodeColourManager &&other) = delete;

    NodeColourManager &operator=(const NodeColourManager &other) = delete;
    NodeColourManager &operator=(const NodeColourManager &&other) = delete;

    static void getInstance(NodeColourManager *&man, DataStorageParser *parser);

    void setColour(NodeData *data);
    QColor getColour(QString &param) const throw(std::out_of_range, std::invalid_argument);
    QColor getColour(QString &&param) const throw(std::out_of_range, std::invalid_argument);

protected:
    NodeColourManager(DataStorageParser *parser) throw(std::invalid_argument);


};

#endif // NODECOLOURMANAGER_H
