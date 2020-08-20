#ifndef VIRTUE_H
#define VIRTUE_H
#include <QString>
#include <QRandomGenerator>

enum VirtueName
{
    Chastity, Temperance, Charity, Diligence, Patience, Kindness, Humility
};

struct Virtue
{
    VirtueName name;
    int amount = 0;

    Virtue(VirtueName);
    void addAmount(int);
    QString getVirtueString(VirtueName);
};

#endif // VIRTUE_H
