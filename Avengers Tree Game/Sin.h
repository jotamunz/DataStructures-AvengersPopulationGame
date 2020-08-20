#ifndef SIN_H
#define SIN_H
#include <QString>
#include <QRandomGenerator>

enum SinName
{
    Lust=1, Gluttony, Greed, Sloth, Wrath, Envy, Pride
};

struct Sin
{
    SinName name;
    int amount = 0;

    Sin(SinName);
    void addAmount(int);
    QString getSinString(SinName);
};

#endif // SIN_H
