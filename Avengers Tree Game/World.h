#ifndef WORLD_H
#define WORLD_H
#include <BinaryTree.h>
#include <DoubleList.h>
#include <HashMapId.h>
#include <Stream.h>
#include <HashMapFamily.h>
#include <HashSport.h>
#include <QVector>
#include <Person.h>
#include <HashThanos.h>

struct World
{
    DoubleList* people;
    BinaryTree* peopleTree;
    Stream* stream;
    HashMapId* hashMapId;
    HashMapFamily* hashMapFamily;
    HashSport * hashSport;
    HashThanos * hashThanos;
    QString worldString;
    QString deathString;
    QString savedString;
    QString infoString;
    QVector<Person*> mostSins;
    QVector<Person*> mostVirtues;
    QStringList infoList;

    World();
    void createPeople(int);
    void buildTree();
    void buildTreeInsert(DoubleList*, Node*, Node*, int);
    void setFriends();
    void setFamily();
    void setSins();
    void setVirtues();
    void addPeopleToTxt();
    Person* findPersonTree(int);
    Person* findPersonAux(int, TreeNode*);
    Person* findPersonList(int, Node*);

    //CONSULTAS
    bool consultWinningTeam();
    QString consultPerson(int);
    void consultFamilyPerson(int);
    void consultFrindsChainPerson(int);
    void consultSport(QString);
    void consultPersonsAlive();
    void consultPersonsDead();
    void consultPersonsSaved();
    void resetVisitedPeople();
    void consultFrindsChainPersonAux(Person*);
    QStringList consultFamilyPerson_aux(int);

    //ANIQUILACION
    QStringList Thanos(int,int);
    void Nebula(int id);
    void NebulaAux(Person*);
    void EbonyMaw(int);
    void EbonyMawAux(Person*);
    void BlackDwarf(QString sport, int n);
    void CorvusGlaive();
    void Corvus_Glaive_aux();
    void Midnight();
    void Midnight_aux();
    QVector<Person*> selectSortSport(QVector<Person*>);
    int aliveQuantity(QVector<Person *> array, int n);
    void heapify (QVector<Person*>, int);
    void insertNode(Person*);
    void heapify(int i);
    void heapifyMin (int i);
    void insertNodeV(Person*);

    //SALVACION
    void Thor();
    void ThorAux(int, TreeNode*, QString*);
    void IronMan();
    void AntMan(int);
    void AntManAux(TreeNode*, QString*);
    void AntManAux2(TreeNode*, int, QVector<int>*, QVector<Node*>*, QVector<QString>*, QString);
    void SpiderMan();
    void SpiderManAux(Node*, int);
    void saveFriends(Person*);
    void saveOffspring(Person*);
    QVector<TreeNode*> squashTree();
    void squashTreeAux(QVector<TreeNode*>*, TreeNode*);

};


#endif // WORLD_H
