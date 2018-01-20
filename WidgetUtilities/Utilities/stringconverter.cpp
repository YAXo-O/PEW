#include <cctype>
#include <stdexcept>
#include <cmath>
#include "stringconverter.h"

/* States */
const int initialState = 0;
const int signState = 1;
const int intDigitState = 2;
const int decimalPointState = 3;
const int fractionalDigitState = 4;
const int finalState = 5;
const int errorState = 6;

StringConverter::StringConverter(): line(nullptr), linePosition(-1), state(errorState)
{
}

float StringConverter::getNumber(const char *_line, int &_linePosition)
{
    line = _line;
    linePosition = _linePosition;
    state = initialState;
    skipSpaces();

    integer = 0;
    fractional = 0;
    fractionalCount = 1;
    bPositive = true;

    while(state != finalState && state != errorState)
    {
        char symbol = line[linePosition];
        switch(state)
        {
        case initialState:
            initialStateProccessor(symbol);

            break;

        case signState:
        case intDigitState:
            intStateProccessor(symbol);

            break;

        case decimalPointState:
            decimalPointStateProccessor(symbol);

            break;

        case fractionalDigitState:
            fractionalStateProccessor(symbol);

            break;

        default:
            state = errorState;

            break;
        }
    }

    _linePosition = linePosition;
    if(state == errorState)
        throw std::invalid_argument("Not a number!");

    float result = integer + fractional;
    if(!bPositive)
        result *= -1;

    line = nullptr;

    return result;
}

float StringConverter::getNumber(const char *_line, int &&_linePosition)
{
    return getNumber(_line, _linePosition);
}

void StringConverter::skipSpaces()
{
    while(isspace(line[linePosition]))
    {
        if(line[linePosition] == '\n' || line[linePosition] == '\0')
        {
            state = errorState;
            break;
        }

        linePosition++;
    }
}

void StringConverter::initialStateProccessor(char symbol)
{
    if(symbol == '-' || symbol == '+')
    {
        if(symbol == '-')
            bPositive = false;
        state = signState;
        linePosition++;
    }
    else if(symbol == '.' || symbol == ',')
    {
        state = decimalPointState;
        linePosition++;
    }
    else if(isdigit(symbol))
    {
        increaseInteger(symbol);
        state = intDigitState;
    }
    else
        state = errorState;
}

void StringConverter::intStateProccessor(char symbol)
{
    if(isdigit(symbol))
        increaseInteger(symbol);
    else if(symbol == '.' || symbol == ',')
    {
        state = decimalPointState;
        linePosition++;
    }
    else if(isspace(symbol) || symbol == '\0')
    {
        state = finalState;
        linePosition++;
    }
    else
        state = errorState;

}

void StringConverter::decimalPointStateProccessor(char symbol)
{
    if(isdigit(symbol))
    {
        increaseFractional(symbol);
        state = fractionalDigitState;
    }
    else
        state = errorState;
}

void StringConverter::fractionalStateProccessor(char symbol)
{
    if(isdigit(symbol))
        increaseFractional(symbol);
    else if(isspace(symbol))
    {
        state = finalState;
        linePosition++;
    }
    else
        state = errorState;
}

void StringConverter::increaseInteger(char symbol)
{
    integer *= 10;
    integer += symbol - '0';
    linePosition++;
}

void StringConverter::increaseFractional(char symbol)
{
    fractional += (symbol - '0')*pow(10, -fractionalCount);
    fractionalCount++;
    linePosition++;
}
