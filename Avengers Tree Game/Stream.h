#ifndef STREAM_H
#define STREAM_H
#include <QString>
#include <fstream>
#include <iostream>
#include <QFile>
#include <QDebug>
#include <QRandomGenerator>
#include <smtp.h>

using namespace std;

enum FileNameTxt
{
    BoyNamesTxt, GirlNamesTxt, LastNamesTxt, CountriesTxt, ReligionsTxt, ProfessionsTxt, SportsTxt
};

enum AlgorithmNameTxt
{
    ThanosTxt, NebulaTxt, EbonyMawTxt, BlackDwarfTxt, CorvusGlaiveTxt, MidnightTxt,
    ThorTxt, IronManTxt, AntManTxt, SpiderManTxt
};

struct Stream
{
    QFile file;
    QVector<QString> arrayBoyNames;
    QVector<QString> arrayGirlNames;
    QVector<QString> arrayLastNames;
    QVector<QString> arrayCountries;
    QVector<QString> arrayReligions;
    QVector<QString> arrayProfessions;
    QVector<QString> arraySports;

    int rangeBoyNames[2] = {0, 0};
    int rangeGirlNames[2] = {0, 0};
    int rangeLastNames[2] = {0, 0};
    int rangeCountries[2] = {0, 0};
    int rangeReligions[2] = {0, 0};
    int rangeProfession[2] = {0, 0};
    int rangeSports[2] = {0, 0};

    Stream();
    void __init__();
    QVector<QString> initArray(QString);
    int lastLine(QString);
    QString randomOutputAux(QVector<QString>, int, int);
    QString randomOutput(QVector<QString>, FileNameTxt);
    void writeWorld(QString);
    void writeSalvation(QString);
    void writeDeath(QString);
    void writeEvent(QString, AlgorithmNameTxt);
    void writeTree(QString);
    void cleanFiles();
    void cleanFilesAux(QString);
    void sendMail(QString topic, QString content, QString path);

};


#endif // STREAM_H
