#ifndef DATE_H
#define DATE_H
#include <QString>

enum Month
{
    January=1, February, March, April, May, June, July, August, September, October, November, December
};

struct Date
{
    int year;
    Month month;
    int day;

    Date();
    Date(int, Month, int);
};

#endif // DATE_H
