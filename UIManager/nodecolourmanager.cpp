#include <QColor>
#include <QMessageBox>
#include "nodecolourmanager.h"
#include "../Nodes/nodedata.h"

QColor NodeColourManager::getColour(QString &param) const throw(std::out_of_range, std::invalid_argument)
{
    QString res = getValue(param);
    QStringList result = getValue(param).split(' ');
    result.removeAll("");
    if(result.count() != 3)
        throw std::invalid_argument("Specified param doesn't hold colour information");

    QColor c;
    for(int i = 0; i < result.count(); i++)
    {
        bool bOk = false;
        double value = result[i].toDouble(&bOk);

        if(bOk)
        {
            switch(i)
            {
            case 0:
                c.setRedF(value);
                break;

            case 1:
                c.setGreenF(value);
                break;

            case 2:
                c.setBlueF(value);
                break;

            default:
                break;
            }
        }
        else
            throw std::invalid_argument(QString("Specified param doesnt't hold colour "
                                        "information: word number " + QString::number(i) + " \"" + result[i] + " \"").toStdString());
    }

    return c;
}

void NodeColourManager::getInstance(NodeColourManager *&man, DataStorageParser *parser)
{
    // Find a way to delete this stuff!
    static NodeColourManager *ndmanager = nullptr;

    if(!ndmanager && parser)
        ndmanager = new NodeColourManager(parser);

    man = ndmanager;
}

void NodeColourManager::setColour(NodeData *data)
{
    if(data)
    {
        try
        {
            data->setBorderColour(getColour(data->getKeyName()));
        }
        catch(const std::out_of_range &except)
        {
            QMessageBox msg;
            msg.setWindowTitle("Error at colour identification");
            msg.setText(except.what());
            msg.setIcon(QMessageBox::Critical);
            msg.exec();
            data->setBorderColour(Qt::black);
        }
        catch(const std::invalid_argument &except)
        {
            QMessageBox msg;
            msg.setWindowTitle("Error at colour identification");
            msg.setText(except.what());
            msg.setIcon(QMessageBox::Critical);
            msg.exec();
            data->setBorderColour(Qt::black);
        }
    }
}

QColor NodeColourManager:: getColour(QString &&param) const throw(std::out_of_range, std::invalid_argument)
{
    return getColour(param);
}

NodeColourManager::NodeColourManager(DataStorageParser *parser) throw(std::invalid_argument): NodeDataManager(parser)
{
}
