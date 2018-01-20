#include "externalvariable.h"

ExternalVariable::ExternalVariable(DataPin *_pin, NodeParamsContainer *_variablePanel):
    pin(_pin), variablePanel(_variablePanel)
{
}

ExternalVariable::~ExternalVariable()
{
}

const void *ExternalVariable::getValue()
{
    const void *pinRes = nullptr;

    if(pin)
    {
        pinRes = pin->readValue();
        if(pinRes)
            return pinRes;
    }

    return variablePanel->getValue();
}

void ExternalVariable::setValue(void *value)
{
    if(pin)
        pin->writeValue(value);
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

bool ExternalVariable::isConnected() const
{
    return pin && pin->isConnected();
}

bool ExternalVariable::isDataPresent() const
{
    return isConnected() && pin->isDataPresent();
}

NodeParamsContainer *ExternalVariable::getParamsContainer() const
{
    return variablePanel;
}
