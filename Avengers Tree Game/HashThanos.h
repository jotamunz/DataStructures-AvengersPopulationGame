#ifndef HASHTHANOS_H
#define HASHTHANOS_H
#include<QVector>
#include<DoubleList.h>
#include<QtAlgorithms>
#include <Stream.h>

struct HashThanos
{
    DoubleList* people;
    QVector<Person*> thanosNaughtyList [100][10]; // age (indexed by 2019 - age = year) and level (indexed by the ponderado)
    QVector<Person*> Totals;
    Stream * stream;

    struct coordenatesChild
    {
        int x = 0; // fila
        int y = 0; // columna
    }coordenatesChild;

    int rangesWeightsTotal [10];
    //WEIGHTS
    int friendshipWeight = 1;
    int familyWeight = 1;
    int ageWeights [9] = {1,1,1,1,1,1,1,1,1}; // Infant, Preschool, School, Puberty, Teen, Young, YoungAdult, MatureAdult, Elderly
    int sinsWeights [7] = {1,1,1,1,1,1,1}; // Lust, Gluttony, Greed, Sloth, Wrath, Envy, Pride
    int virtueWeights [7] = {1,1,1,1,1,1,1}; // Chastity, Temperance, Charity, Diligence, Patience, Kindness, Humility
    int travelWeights = 1;
    int exerciseWeight = 1;
    int sportsWeight = 1;

    HashThanos(DoubleList*,Stream*);
    //FUNCTIONS GET AMOUNT
    int getFriendsAmount(Person *);
    int getfamilyAmount(Person *);
    int getAgeAmount(Person *);
    int getSinsAmount(Person *);
    int getVirtueAmount(Person *);
    int getTravelAmount(Person *);
    int getExcerciseWeight(Person *);
    //TOTAL
    void setTotalWeight(Person *);
    void indexPersonTotals();
    void selectSortThanos();
    //HASH
    void indexHashThanos();
    int getIndexYear(int);
    QStringList doJustice(int,int);
    QStringList doJusticeLevel(int level);
    QStringList doJusticeYear(int year);
    QStringList doJustice_aux(int year, int level);
    void clean();
};

#endif // HASHTHANOS_H
