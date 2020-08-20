#ifndef PERSON_H
#define PERSON_H
#include <QString>
#include <Date.h>
#include <QRandomGenerator>
#include <Sin.h>
#include <Virtue.h>
#include <QStringList>
#include <Stream.h>
#include <HashMapId.h>
#include <QDateTime>

enum MaritalStatus
{
    Single, Married, Divorced
};
enum AgeGroup
{
    Infant, Preschool, School, Puberty, Teen, Young, YoungAdult, MatureAdult, Elderly
};
enum Gender
{
    Male, Female
};
enum State
{
    Alive, Dead, Saved
};

struct Person
{
    Stream* stream;

    int id;
    QString name;
    QString lastName;

    Gender gender;
    QString religion;
    QString profession;

    Date* birthDate;
    int age;
    AgeGroup ageGroup;

    Person* friends[50];
    MaritalStatus maritalStatus;
    Person* spouse = nullptr;
    Person* children[4];
    Person* parents[2];

    bool hasParent = false;
    bool visited = false;

    int weeklyExercise;
    QString sportsPracticed[3];

    QString livingLocation;
    QString livingContinent;
    QString livingCountry;
    QString visitedCountries[50];

    State state = Alive;
    int lifeScore = 0;

    Sin* sins[7];
    Virtue* virtues[7];
    int totalSins = 0;
    int totalVirtues = 0;

    Person(Stream*, HashMapId*);
    void initSinsAndVirtues();
    void initFamilyAndFriends();
    Gender generateGender();
    QString generateName();
    Date* generateBirthDate();
    AgeGroup generateAgeGroup();
    MaritalStatus generateMaritalStatus();
    void generateLivingLocation();
    void generateSportsPracticed();
    void generateVisitedCountries();
    bool countryInArray(QString);
    bool friendInArray(Person*);
    bool isEmptyFriends();
    QString toString();
    QString toStringConsult();
    QString ageGroupString(AgeGroup);
    QString genderString(Gender);
    QString maritalStatusString(MaritalStatus);
    QString stateString(State);
};







#endif // PERSON_H

