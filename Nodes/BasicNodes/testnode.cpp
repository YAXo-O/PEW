#include "testnode.h"
#include "../externalvariablefactory.h"
#include "../Data/booldata.h"

#include <QDebug>

TestNode::TestNode(QString nodeName, QWidget *parent): BaseNode(nodeName,parent),
        read(ExternalVariableFactory::createExternal(BoolData::dataType_s(), "Read Pin", DFF_READ)),
        write(ExternalVariableFactory::createExternal(BoolData::dataType_s(), "Write Pin", DFF_WRITE)),
        both(ExternalVariableFactory::createExternal(BoolData::dataType_s(), "Both Pin", DFF_BOTH))
{
    addDataPin(read->getPin());
    addDataPin(write->getPin());
    addDataPin(both->getPin());
    addInput("Input name", "input slot");
    rearangeInputs();
    rearangePins();
}

TestNode::~TestNode()
{
}

/*
void TestNode::enable(BaseNode *caller)
{
    qDebug() << *((bool*)(read->getValue()));
    qDebug() << *((bool*)(write->getValue()));
    qDebug() << *((bool*)(both->getValue()));

    BaseNode::enable(caller);
}
*/
