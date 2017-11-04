#include "externalvariable.h"

ExternalVariable::ExternalVariable(DataPin *_pin, QWidget *_variablePanel):
    pin(_pin), variablePanel(_variablePanel)
{
}

void *ExternalVariable::getValue()
{
    if(pin)
        return pin->readValue();

    return nullptr;
}

void ExternalVariable::setValue(void *)
{
    // Sets value(if can)
}

const char *ExternalVariable::getType()
{
    if(!pin)
        return nullptr;
    else
        return pin->getType();
}

DataPin *ExternalVariable::getPin()
{
    return pin;
}

const QString &ExternalVariable::getVarName()
{
    return pin->getName();
}
