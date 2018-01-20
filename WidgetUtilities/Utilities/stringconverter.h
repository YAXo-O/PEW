#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

class StringConverter
{
public:
    StringConverter();
    ~StringConverter() = default;

    float getNumber(const char *line, int &linePosition);
    float getNumber(const char *line, int &&linePosition);

private:
    const char *line;
    int linePosition;
    int state;

    float integer;
    float fractional;
    bool bPositive;
    int fractionalCount;

    void skipSpaces();
    void initialStateProccessor(char symbol);
    void intStateProccessor(char symbol);
    void decimalPointStateProccessor(char symbol);
    void fractionalStateProccessor(char symbol);

    void increaseInteger(char symbol);
    void increaseFractional(char symbol);
};

#endif // TOFLOAT_H
