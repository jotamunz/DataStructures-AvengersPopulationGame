#ifndef HASHMAPFAMILY_H
#define HASHMAPFAMILY_H

#include <QString>
#include <QRandomGenerator>
#include <qdebug.h>
#include <QVector>
#include <Person.h>
#include <QLinkedList>
#include <DoubleList.h>
#include <Stream.h>
#include <array>


struct HashMapFamily
{

    struct coordenatesChild
    {
        int x = 0; // fila
        int y = 0; // columna
    }coordenatesChild;

    QVector<Person*> hashMapChilds[50][8]; //[Country][AgeGroup]
    QVector<Person*> arrayYoung;
    QVector<Person*> arrayYoungAdult;
    QVector<Person*> arrayMatureAdult;
    QVector<Person*> arrayElderly;

    void hashChild(Person*, Stream*, int);
    int hashChildCountry(Person *, Stream*);
    void addToHashChildren(Person *, Stream *);
    void emptyHash(Person*);
    void makeFamily(QVector<Person*>, Stream * );
    void makeFamilySameAge(Stream * );
    void makeFamilyDifferentAge(Person *, Stream * );
    void findChildrens(Person *, Stream *, int);
    void addToArraysMarried(Person*);
    void MarryPersons(Stream *);
    void MarryPersonSameAge(QVector<Person*>);
    void MarryPersonOlder(QVector<Person*> ,QVector<Person*>);
    void DeclareSingle(QVector<Person*>);

};

#endif // HASHMAPFAMILY_H
