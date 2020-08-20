#include <Virtue.h>

Virtue::Virtue(VirtueName _name)
{
    this->name = _name;
}

void Virtue::addAmount(int sinAmount)
{
    this->amount += sinAmount;
}


QString Virtue::getVirtueString(VirtueName virtueName)
{
    QString state[7] = {"Chastity", "Temperance", "Charity", "Diligence", "Patience", "Kindness", "Humility"};
    return state[virtueName];
}
