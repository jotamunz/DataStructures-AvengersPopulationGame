#include <Sin.h>

Sin::Sin(SinName _name)
{
    this->name = _name;
}

void Sin::addAmount(int sinAmount)
{
    this->amount += sinAmount;
}

QString Sin::getSinString(SinName sinName)
{
    QString state[7] = {"Lust", "Gluttony", "Greed", "Sloth", "Wrath", "Envy", "Pride"};
    return state[sinName];
}
