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
    appendExternalParamsWidget(read->getParamsContainer()->getParamsPanel());
    appendExternalParamsWidget(both->getParamsContainer()->getParamsPanel());
    addInput("Input name", "input slot");
    rearangeInputs();
    rearangePins();
}

TestNode::~TestNode()
{
}

void TestNode::enable(BaseNode *caller)
{
    qDebug() << "Read-only state: " << *((bool*)(read->getValue()));
    qDebug() << "Read-write state: " << *((bool*)(both->getValue()));
    bool t = true;
    write->setValue(&t);

    BaseNode::enable(caller);
}
