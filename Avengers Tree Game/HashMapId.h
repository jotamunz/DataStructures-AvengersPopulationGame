#ifndef HASHMAPID_H
#define HASHMAPID_H
#include <qdebug.h>
#include <QRandomGenerator>

struct HashMapId
{
    struct arrayRandom
    {
        int arrayRandom[100000];
    };

    struct coordenatedRandom
    {
        int x = 0;
        int y = 0;
    }coordenateRandom;

    arrayRandom* hashMapRandom[10][10];

    HashMapId();
    void hashRandom(int);
    bool addHashRandom(int);
    void initArrayRandom();
    int cuentaDigitos(int);
    int getRandom();
};


#endif // HASHMAPID_H
