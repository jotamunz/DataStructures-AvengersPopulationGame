#ifndef HASHSPORT_H
#define HASHSPORT_H

#include <QString>
#include <QRandomGenerator>
#include <qdebug.h>
#include <QVector>
#include <Person.h>
#include <QLinkedList>
#include <DoubleList.h>
#include <Stream.h>
#include <array>

struct HashSport
{
    QVector<Person*> arraySports[40];

    void addToArraySports(Person *, Stream*);
};

#endif // HASHSPORT_H
