#include <World.h>
#include <algorithm>

World::World()
{
    this->people = new DoubleList();
    this->stream = new Stream();
    this->hashMapId = new HashMapId();
    this->hashMapFamily = new HashMapFamily();
    this->hashSport = new HashSport();
    this->hashThanos = new HashThanos(this->people, this->stream);
    this->mostSins.append(nullptr);
    this->mostVirtues.append(nullptr);
}

void World::createPeople(int amount)
{
    QString result;
    for (int i = 0; i < amount; i++)
    {
        Person * tempPerson = new Person(this->stream, this->hashMapId);
        this->people->insertOrdered(tempPerson);
        this->hashMapFamily->addToArraysMarried(tempPerson);
        this->hashMapFamily->addToHashChildren(tempPerson, this->stream);
        this->hashSport->addToArraySports(tempPerson, this->stream);
    }
    this->hashMapFamily->MarryPersons(this->stream);
    this->setFriends();
    this->buildTree();
    this->addPeopleToTxt();
}

void World::addPeopleToTxt()
{
    Node* temp = people->first;
    int count = 0;
    while (temp != nullptr)
    {
        count++;
        worldString += temp->person->toStringConsult();
        temp = temp->next;
    }
    this->stream->writeWorld(worldString);
    this->stream->writeTree(this->peopleTree->print());
}

//--------------------------------------------TREE--------------------------------------------

int nextPowerOf2(int n, int* count)
{
    int power = 2;
    while(power < n)
    {
        power *= 2;
        (*count)++;
    }
    return power;
}

Node* findMiddleNode(DoubleList* list, Node* indexStart, Node* indexEnd)
{
    Node* fast = indexStart;
    Node* slow = indexStart;
    if (!list->isEmpty())
    {
        while(fast != indexEnd && fast->next != indexEnd)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    return nullptr;
}

void World::buildTreeInsert(DoubleList* list, Node* indexStart, Node* indexEnd, int level)
{
    if (level > 0)
    {
        Node* middleNode = findMiddleNode(people, indexStart, indexEnd);
        peopleTree->insert(middleNode);
        buildTreeInsert(list, indexStart, middleNode, level - 1);
        buildTreeInsert(list, middleNode->next, indexEnd, level - 1);
    }
}

void World::buildTree()
{
    this->peopleTree = new BinaryTree();
    int onePercent = (this->people->size/100);
    int maxLevelNeeded = 1;
    int nodeAmount = nextPowerOf2(onePercent, &maxLevelNeeded) - 1;
    //qDebug() << "Node amount:" << nodeAmount << "Tree height:" << maxLevelNeeded;
    if (nodeAmount <= people->size)
        buildTreeInsert(people, people->first, people->last, maxLevelNeeded);
}

Person * World::findPersonTree(int id)
{
    return findPersonAux(id, peopleTree->root);
}

Person * World::findPersonAux(int id, TreeNode * node)
{
    if (node == nullptr)
        return nullptr;
    else if (id == node->personNode->person->id)
        return node->personNode->person;
    else if (node->isLeaf())
        return findPersonList(id, node->personNode);
    else if (id < node->personNode->person->id)
        return findPersonAux(id, node->leftSon);
    else
        return findPersonAux(id, node->rightSon);
}

Person * World::findPersonList(int id, Node * personNode)
{
    if (id < personNode->person->id)
    {
        while(personNode != nullptr && id <= personNode->person->id)
        {
            if (personNode->person->id == id)
                return  personNode->person;
            personNode = personNode->previous;
        }
    }
    else
    {
        while(personNode != nullptr && id >= personNode->person->id)
        {
            if (personNode->person->id == id)
                return  personNode->person;
            personNode = personNode->next;
        }
    }
    return nullptr;
}

//--------------------------------------------SETS--------------------------------------------

void World::setSins()
{
    Node* temp = this->people->first;
    while (temp != nullptr)
    {
        for (int i = 0; i < 7; i++)
        {
           int sinAmount = static_cast<int>(QRandomGenerator::global()->generate() % 100);
           temp->person->sins[i]->addAmount(sinAmount);
           temp->person->totalSins += sinAmount;
        }
        temp = temp->next;
    }
}

void World::setVirtues()
{
    Node* temp = this->people->first;
    while (temp != nullptr)
    {
        for (int i = 0; i < 7; i++)
        {
           int virtueAmount = static_cast<int>(QRandomGenerator::global()->generate() % 100);
           temp->person->virtues[i]->addAmount(virtueAmount);
           temp->person->totalVirtues += virtueAmount;
        }
        temp = temp->next;
    }
}

void World::setFriends()
{
    Node* currentPerson = this->people->first;
    while (currentPerson != nullptr)
    {
        if (currentPerson->person->isEmptyFriends())
        {
            int friendAmount;
            do
            {
                friendAmount = static_cast<int>(QRandomGenerator::global()->generate() % 50);
            } while(friendAmount > people->size - 1);
            for (int i = 0; i < friendAmount; i++)
            {
                int randomNode;
                Node* friendCandidate;
                do
                {
                    randomNode = static_cast<int>(QRandomGenerator::global()->generate() % unsigned (people->size));
                    friendCandidate = people->getPosition(randomNode);
                } while(friendCandidate == currentPerson || currentPerson->person->friendInArray(friendCandidate->person));
                if (friendCandidate->person->livingCountry == currentPerson->person->livingCountry)
                {
                    currentPerson->person->friends[i] = friendCandidate->person;
                    continue;
                }
                else
                {
                    int rand = static_cast<int>(QRandomGenerator::global()->generate() % 100);
                    if (rand < 40)
                    {
                        currentPerson->person->friends[i] = friendCandidate->person;
                        continue;
                    }
                    else
                    {
                        bool friendInCommon = false;
                        for (int j = 0; j < 50; j++)
                        {
                            if (friendCandidate->person->friends[j] != nullptr)
                            {
                                if (currentPerson->person->friendInArray(friendCandidate->person->friends[j]))
                                {
                                    friendInCommon = true;
                                    break;
                                }
                            }
                            else break;
                        }
                        if (friendInCommon)
                        {
                            int rand = static_cast<int>(QRandomGenerator::global()->generate() % 100);
                            if (rand < 70)
                            {
                                currentPerson->person->friends[i] = friendCandidate->person;
                                continue;
                            }
                        }
                    }
                }
            }
        }
        currentPerson = currentPerson->next;
    }
}

//---------------------------------------CONSULTAS--------------------------------------------

bool World::consultWinningTeam()
{
    Node* temp = this->people->first;
    int avengers = 0;
    int thanos = 0;
    while (temp != nullptr)
    {
        if (temp->person->state == Saved || temp->person->state == Alive)
            avengers++;
        else
            thanos++;
        temp = temp->next;
    }
    if (avengers >= thanos)
        return true;
    return false;
}

QString World::consultPerson(int id)
{
    infoString = "";
    Person * person = this->findPersonTree(id);
    if (person != nullptr)
    {
        infoString = person->toString();
    }
    else
    {
        infoString = "No existe la persona de id:";
    }

    return infoString;
}

void World::consultFamilyPerson(int id)
{

    Person * person = this->findPersonTree(id);
    if (person != nullptr)
    {
        for(int i = 0; i < 4; i++)
        {
            if(person->children[i] != nullptr)
            {
                this->infoList.append(person->children[i]->toString());
                consultFamilyPerson(person->children[i]->id);
            }
            else break;
        }
    }
    else
        qDebug().noquote() << "No existe la persona de id:" << id;
}

QStringList World::consultFamilyPerson_aux(int id)
{
    this->infoList.clear();
    this->consultFamilyPerson(id);
    return this->infoList;
}

void World::consultFrindsChainPerson(int id)
{
    this->infoList.clear();
    Person * person = this->findPersonTree(id);
    if (person != nullptr)
    {
        this->consultFrindsChainPersonAux(person);
        this->resetVisitedPeople();
    }
    else
       qDebug().noquote() << "No existe la persona de id:" << id;
}

void World::consultFrindsChainPersonAux(Person * person)
{
    infoString = "";
    for(int i = 0; i < 50; i++)
    {
        if (person->friends[i] != nullptr)
        {
            if(person->friends[i]->visited == false)
            {
                this->infoList.append(person->friends[i]->toString());
                person->friends[i]->visited = true;
                consultFrindsChainPersonAux(person->friends[i]);
            }
        }
        else break;
    }
}

void World::consultSport(QString sport)
{
    infoList.clear();
    for(int i = 0; i < stream->arraySports.length(); i++)
    {
        if(stream->arraySports.at(i) == sport)
        {
            for(int j = 0; j < this->hashSport->arraySports[i].length(); j++)
            {
                infoList.append(this->hashSport->arraySports[i].at(j)->toString());
            }
            break;
        }
    }
}

void World::consultPersonsAlive()
{
    infoList.clear();
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        if(temp->person->state == Alive || temp->person->state == Saved)
        {
            this->infoList.append("ID: " + QVariant(temp->person->id).toString() + " Name: " + temp->person->name);
        }
        temp = temp->next;
    }
}

void World::consultPersonsDead()
{
    infoList.clear();
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        if(temp->person->state == Dead)
        {
            this->infoList.append("ID: " + QVariant(temp->person->id).toString() + " Name: " + temp->person->name);
        }
        temp = temp->next;
    }
}

void World::consultPersonsSaved()
{
    infoList.clear();
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        if(temp->person->state == Saved)
        {
            this->infoList.append("ID: " + QVariant(temp->person->id).toString() + " Name: " + temp->person->name);
        }
        temp = temp->next;
    }
}

void World::resetVisitedPeople()
{
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        temp->person->visited = false;
        temp = temp->next;
    }
}

//---------------------------------------ANIQUILACION--------------------------------------------

QStringList World::Thanos(int year, int level)
{
    this->hashThanos->clean();

    infoList.clear();
    int counter = 0;
    hashThanos->indexPersonTotals();
    for(int i = 0; i < this->hashThanos->Totals.length(); i++)
        counter ++;

    hashThanos->indexHashThanos();

    if(year != -1 && level != -1)
        this->infoList = hashThanos->doJustice(year,level);
    else if(level == -1)
         this->infoList = hashThanos->doJusticeYear(year);
    else if(year == -1)
        this->infoList = hashThanos->doJusticeLevel(level);

    return infoList;
}

void World::Nebula(int id)
{
    infoList.clear();
    this->infoString = "";
    this->deathString = "";
    Person * person = this->findPersonTree(id);
    if (person != nullptr)
    {
        this->NebulaAux(person);
        infoString += "\n";
        infoString += "\n";
        this->stream->writeEvent(infoString, NebulaTxt);
        this->stream->writeDeath(deathString);
        this->stream->writeEvent(deathString, NebulaTxt);
        this->resetVisitedPeople();
    }
    else
       qDebug().noquote() << "No existe la persona de id:" << id;
}

void World::NebulaAux(Person * person)
{
    for(int i = 0; i < 50; i++)
    {
        if (person->friends[i] != nullptr)
        {
            if(person->friends[i]->visited == false && person->friends[i]->state != Dead)
            {
                infoString += "Person: "+ person->friends[i]->name + " killed for being friends with " + person->name + "\n";
                person->friends[i]->visited = true;
                person->friends[i]->state = Dead;
                this->deathString += "Nebula: " + person->friends[i]->toStringConsult();
                this->infoList.append("ID: " + QVariant(person->id).toString() + " Name: " + person->name + " killed");
                NebulaAux(person->friends[i]);
            }
        }
        else break;
    }
}

void World::EbonyMaw(int id)
{
    infoList.clear();
    this->infoString = "";
    this->deathString = "";
    Person * person = this->findPersonTree(id);
    if (person != nullptr)
    {
        this->EbonyMawAux(person);
        infoString += "\n";
        infoString += "\n";
        this->stream->writeEvent(infoString, EbonyMawTxt);
        this->stream->writeEvent(deathString, EbonyMawTxt);
        this->stream->writeDeath(deathString);
    }
    else
       qDebug().noquote() << "No existe la persona de id:" << id;
}

void World::EbonyMawAux(Person* person)
{
    this->infoList.append("ID: " + QVariant(person->id).toString() + " Name: " + person->name + " selected");
    for(int i = 0; i < 4; i++)
    {
        if(person->children[i] != nullptr)
        {
            if (person->children[i]->state != Dead)
            {
                person->children[i]->state = Dead;
                this->deathString += "Ebony Maw: " + person->children[i]->toStringConsult();
                infoString += "Child: "+ person->children[i]->name + " killed for being a child of " + person->name + " and " + person->spouse->name + "\n";
                EbonyMawAux(person->children[i]);
            }
        }
        else break;
    }
}

void World::BlackDwarf(QString sport, int n)
{
    infoList.clear();
    QString informationString = "";
    QVector<Person *> arrayTemp;
    int indexSport = -1;
    int killingAmount = 0;
    int aliveAmount = 0;
    this->deathString = "";

    for(int i = 0; i < this->stream->arraySports.length(); i++)
    {
        if(this->stream->arraySports[i].toLower() == sport.toLower())
            indexSport = i;
    }
    if(indexSport != -1)
    {
        arrayTemp = this->selectSortSport(this->hashSport->arraySports[indexSport]);
        aliveAmount = aliveQuantity(arrayTemp,n);
        killingAmount = aliveAmount/2;
        informationString += "Total in: " + sport + " alive : " + QVariant(aliveAmount).toString() + "\n";
        informationString += "Total in: " + sport + " to be killed : " + QVariant(killingAmount).toString() + "\n";
        if(killingAmount > 0)
        {
            for(int i = arrayTemp.length()-1; i > 0; i--)
            {
                if(arrayTemp[i]->weeklyExercise == n && killingAmount != 0)
                {
                    killingAmount -= 1;
                    arrayTemp[i]->state = Dead;
                    this->infoList.append("ID: " + QVariant(arrayTemp[i]->id).toString() + " Name: " + arrayTemp[i]->name + " killed");
                    informationString += "Black Dwarf killed : " + arrayTemp[i]->name + "for practicing" + sport + " " + QVariant(n).toString() + " times a day" + "\n";
                    deathString += "Black Dwarf: " + arrayTemp[i]->toStringConsult();
                }
                else if(arrayTemp[i]->weeklyExercise == n)
                {
                    informationString += "Black Dwarf didn't kill : " + arrayTemp[i]->name + "for practicing" + sport + " " + QVariant(arrayTemp[i]->weeklyExercise).toString() + " times a day" + "\n";
                }
            }
        }
        else
            qDebug() << "BlackDwarf no encontro a ningun sobreviviente";
    }
    informationString +="\n";
    informationString +="\n";
    this->stream->writeDeath(deathString);
    this->stream->writeEvent(informationString, BlackDwarfTxt);
    this->stream->writeEvent(deathString, BlackDwarfTxt);
}

void World::CorvusGlaive()
{
    infoList.clear();
    QString informationString = "";
    this->Corvus_Glaive_aux();
    this->deathString = " ";
    int counter = 0;
    int index = 1;
    qDebug() << "length: "<< this->mostSins.length() << endl;
    for(int i = 1; i < this->mostSins.length(); i++)
    {
        if(this->mostSins[i]->state == Alive || this->mostSins[index]->state == Saved )
            counter++;
    }
    counter = (counter*5)/100;
    qDebug() << "counter: " << counter << endl;
    while(counter > 0 && index < this->mostSins.length() )
    {
        if(this->mostSins[index]->state == Alive || this->mostSins[index]->state == Saved )
        {
            this->mostSins[index]->state = Dead;
            counter--;
            this->infoList.append("ID: " + QVariant( mostSins[index]->id).toString() + " Name: " +  mostSins[index]->name + " killed");
            deathString += "Corvus Glaive: " + mostSins[index]->toStringConsult();
            index++;
        }
    }
    this->stream->writeDeath(deathString);
    this->stream->writeEvent(deathString, CorvusGlaiveTxt);
}

void World::Corvus_Glaive_aux()
{
    qDebug() << "entre: " << endl;
    this->mostSins.clear();
    qDebug() << "length_aux: "<< this->mostSins.length() << endl;
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        if(temp->person->state != Dead)
            this->insertNode(temp->person);
        temp = temp->next;
    }
}

void World::Midnight()
{
    infoList.clear();
    QString informationString = "";
    this->Midnight_aux();
    this->deathString = "";
    int counter = 0;
    int index = 1;
    for(int i = 1; i < this->mostVirtues.length(); i++)
    {
        if(this->mostVirtues[i]->state == Alive ||  this->mostVirtues[index]->state == Saved)
            counter++;
    }
    counter = (counter*5)/100;
    while(counter > 0 && index < this->mostVirtues.length() )
    {
        if(this->mostVirtues[index]->state == Alive ||  this->mostVirtues[index]->state == Saved)
        {
            this->mostVirtues[index]->state = Dead;
            counter--;
            this->infoList.append("ID: " + QVariant( mostVirtues[index]->id).toString() + " Name: " +  mostVirtues[index]->name + " killed");
            deathString += "Midnight: " + mostVirtues[index]->toStringConsult();
            index++;
        }
    }
    this->stream->writeDeath(deathString);
    this->stream->writeEvent(deathString, MidnightTxt);
}

void World::Midnight_aux()
{
    this->mostVirtues.clear();
    Node * temp = this->people->first;
    while(temp != nullptr)
    {
        if(temp->person->state != Dead)
           this->insertNodeV(temp->person);
        temp = temp->next;
    }
}

QVector<Person *> World::selectSortSport(QVector<Person *> array)
{
    for(int i = 0; i < array.length(); i ++)
    {
        int min = i;
        for(int j = i; j < array.length(); j++)
        {
            if(array[j]->weeklyExercise < array[min]->weeklyExercise)
                min = j;
        }
        if(i != min)
        {
            Person* temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
    return array;
}

int World::aliveQuantity(QVector<Person *> array, int n)
{
    int quantity = 0;
    for(int i = 0; i < array.length(); i++)
    {
        if((array[i]->state == Alive || array[i]->state == Saved) && array[i]->weeklyExercise == n)
            quantity++;
    }
    return quantity;
}

void World::heapify(int i)
{
    int parent = i /2;
    if(parent > 0)
    {
        if(this->mostSins[i]->totalSins > this->mostSins[parent]->totalSins)
        {
            int temp = this->mostSins[i]->totalSins;
            this->mostSins[i]->totalSins = this->mostSins[parent]->totalSins;
            this->mostSins[parent]->totalSins = temp;
            heapify(parent);
        }
    }
}

void World::insertNode(Person * person)
{
    this->mostSins.append(person);
    heapify (this->mostSins.length()-1);
}

void World::heapifyMin(int i)
{
    int parent = i /2;
    if(parent > 0)
    {
        if(this->mostVirtues[i]->totalVirtues < this->mostVirtues[parent]->totalVirtues)
        {
            int temp = this->mostVirtues[i]->totalVirtues;
            this->mostVirtues[i]->totalVirtues = this->mostVirtues[parent]->totalVirtues;
            this->mostVirtues[parent]->totalVirtues = temp;
            heapifyMin(parent);
        }
    }
}

void World::insertNodeV(Person * person)
{
    this->mostVirtues.append(person);
    heapifyMin (this->mostVirtues.length()-1);
}

//---------------------------------------SALVACION--------------------------------------------

void World::Thor()
{
    infoList.clear();
    this->savedString = "";
    int randomLevel = static_cast<int>(QRandomGenerator::global()->generate() % unsigned (this->peopleTree->height()));
    QString treeLevel = "Tree Level " + QVariant(randomLevel+1).toString() + ": ";
    ThorAux(randomLevel, this->peopleTree->root, &treeLevel);
    this->stream->writeSalvation(savedString);
    this->savedString = (treeLevel + "\n" + this->savedString);
    this->stream->writeEvent(savedString, ThorTxt);
}

void World::ThorAux(int level, TreeNode* node, QString * treeLevel)
{
    if (node != nullptr)
    {
        if (level == 0)
        {
            (*treeLevel) += QVariant(node->personNode->person->id).toString() + " ";
            if (node->personNode->person->spouse != nullptr)
                this->saveFriends(node->personNode->person->spouse);
            for (int i = 0; i < 2; i++)
            {
                if (node->personNode->person->parents[i] != nullptr)
                    this->saveFriends(node->personNode->person->parents[i]);
            }
            for (int i = 0; i < 4; i++)
            {
                if (node->personNode->person->children[i] != nullptr)
                    this->saveFriends(node->personNode->person->children[i]);
            }
        }
        else
        {
            ThorAux(level-1, node->leftSon, treeLevel);
            ThorAux(level-1, node->rightSon, treeLevel);
        }
    }
}

void World::saveFriends(Person* person)
{
    for (int i = 0; i < 50; i++)
    {
        if (person->friends[i] != nullptr)
        {
            if (person->friends[i]->state == Dead)
            {
                person->friends[i]->state = Saved;
                this->infoList.append("ID: " + QVariant( person->friends[i]->id).toString() + " Name: " +  person->friends[i]->name + " saved");
                this->savedString += "Thor: " + person->friends[i]->toStringConsult();
            }
        }
        else break;
    }
}

void World::IronMan()
{
    infoList.clear();
    this->savedString = "";
    QString bombedNodes = "Bombed Nodes: ";
    QVector<TreeNode*> squashedTree = this->squashTree();
    int randomPercent = static_cast<int>(QRandomGenerator::global()->generate() % (60 - 40) + 40);
    int bombAmount = (this->peopleTree->nodeAmount * randomPercent)/100;
    int randomPos;
    for (int i = 0; i < bombAmount; i++)
    {
        do
        {
            randomPos = static_cast<int>(QRandomGenerator::global()->generate() % unsigned(this->peopleTree->nodeAmount));
        }while(randomPos >= squashedTree.size() || squashedTree.at(randomPos)->marks != 0);
        TreeNode * bombedNode = squashedTree.at(randomPos);
        bombedNode->marks = 1;
        bombedNodes += QVariant(bombedNode->personNode->person->id).toString() + " ";
        this->saveOffspring(bombedNode->personNode->person);
    }
    this->stream->writeSalvation(savedString);
    this->savedString = (bombedNodes + "\n" + this->savedString);
    this->stream->writeEvent(savedString, IronManTxt);
    this->peopleTree->resetMarks();
    this->resetVisitedPeople();
}

QVector<TreeNode*> World::squashTree()
{
    QVector<TreeNode*> squashedTree;
    squashTreeAux(&squashedTree, this->peopleTree->root);
    return squashedTree;
}

void World::squashTreeAux(QVector<TreeNode*>* array, TreeNode* node)
{
    if (node != nullptr)
    {
        squashTreeAux(array, node->leftSon);
        (*array).append(node);
        squashTreeAux(array, node->rightSon);
    }
}

void World::saveOffspring(Person* person)
{
    for (int i = 0; i < 4; i++)
    {
        if (person->children[i] != nullptr)
        {
            if (person->children[i]->visited == false && person->children[i]->state == Dead)
            {
                person->children[i]->visited = true;
                person->children[i]->state = Saved;
                this->infoList.append("ID: " + QVariant( person->children[i]->id).toString() + " Name: " +  person->children[i]->name + " saved");
                this->savedString += "Iron Man: " + person->children[i]->toStringConsult();
                saveOffspring(person->children[i]);
            }
        }
        else break;
    }
}

void World::AntMan(int antAmount)
{
    infoList.clear();
    this->savedString = "";
    QString allPaths = "";
    for (int i = 0; i < antAmount; i++)
    {
        allPaths += "Path #" + QVariant(i).toString() + " ";
        AntManAux(this->peopleTree->root, &allPaths);
        allPaths += "\n";
    }
    QVector<int> pathMarks;
    QVector<Node*> paths;
    QVector<QString> pathArray;
    AntManAux2(this->peopleTree->root, 0, &pathMarks, &paths, &pathArray, "");
    int pathIndex1 = pathMarks.indexOf(*std::max_element(pathMarks.constBegin(), pathMarks.constEnd()));
    Node * indexStart = paths.at(pathIndex1);
    allPaths += "Selected Path 1: " + pathArray.at(pathIndex1) + "\n";
    pathMarks.remove(pathIndex1);
    paths.remove(pathIndex1);
    pathArray.remove(pathIndex1);
    int pathIndex2 = pathMarks.indexOf(*std::max_element(pathMarks.constBegin(), pathMarks.constEnd()));
    Node * indexEnd = paths.at(pathIndex2);
    allPaths += "Selected Path 2: " + pathArray.at(pathIndex2) + "\n";
    if (indexStart->person->id > indexEnd->person->id)
    {
        Node * temp = indexStart;
        indexStart = indexEnd;
        indexEnd = temp;
    }
    while(indexStart != nullptr && indexStart->person->id <= indexEnd->person->id)
    {
        if (indexStart->person->state == Dead)
        {
            indexStart->person->state = Saved;
            this->infoList.append("ID: " + QVariant( indexStart->person->id).toString() + " Name: " + indexStart->person->name + " saved");
            this->savedString += "Ant Man: " + indexStart->person->toStringConsult();
        }
        indexStart = indexStart->next;
    }
    this->stream->writeSalvation(savedString);
    this->savedString = (allPaths + "\n" + this->savedString);
    this->stream->writeEvent(savedString, AntManTxt);
    this->peopleTree->resetMarks();
}

void World::AntManAux(TreeNode* node, QString * allPaths)
{
    if (node != nullptr)
    {
        node->marks += 1;
        (*allPaths) += QVariant(node->personNode->person->id).toString() + " ";
        int randomDirection = static_cast<int>(QRandomGenerator::global()->generate() % 2);
        if (randomDirection == 0)
            AntManAux(node->leftSon, allPaths);
        else
            AntManAux(node->rightSon, allPaths);
    }
}

void World::AntManAux2(TreeNode* node, int markAmount, QVector<int>* pathMarks, QVector<Node*>* paths, QVector<QString>* pathArray, QString path)
{
    if (node != nullptr)
    {
        markAmount += node->marks;
        path += QVariant(node->personNode->person->id).toString() + " ";
        if (node->isLeaf())
        {
            (*pathMarks).append(markAmount);
            (*paths).append(node->personNode);
            (*pathArray).append(path);
        }
        else
        {
            AntManAux2(node->leftSon, markAmount, pathMarks, paths, pathArray, path);
            AntManAux2(node->rightSon, markAmount, pathMarks, paths, pathArray, path);
        }
    }
}

void World::SpiderMan()
{
    infoList.clear();
    this->savedString = "";
    QString webNodes = "Spider Web Nodes: ";
    QVector<TreeNode*> squashedTree = this->squashTree();
    int webAmount = static_cast<int>(QRandomGenerator::global()->generate() % unsigned (this->peopleTree->nodeAmount) + 1);
    int randomPos;
    for (int i = 0; i < webAmount; i++)
    {
        do
        {
            randomPos = static_cast<int>(QRandomGenerator::global()->generate() % unsigned(this->peopleTree->nodeAmount));
        }while(randomPos >= squashedTree.size() || squashedTree.at(randomPos)->marks != 0);
        TreeNode * webNode = squashedTree.at(randomPos);
        webNode->marks = 1;
        webNodes += "-> " + QVariant(webNode->personNode->person->id).toString() + " ";
        if (webNode->isLeaf())
            this->SpiderManAux(webNode->personNode, webAmount);
    }
    this->stream->writeSalvation(savedString);
    this->savedString = (webNodes + "\n" + this->savedString);
    this->stream->writeEvent(savedString, SpiderManTxt);
    this->peopleTree->resetMarks();
}

void World::SpiderManAux(Node * indexStart, int saveAmount)
{
    while(indexStart != nullptr && saveAmount > 0)
    {
        if (indexStart->person->state == Dead)
        {
            indexStart->person->state = Saved;
            this->infoList.append("ID: " + QVariant( indexStart->person->id).toString() + " Name: " + indexStart->person->name + " saved");
            this->savedString += "Spider Man: " + indexStart->person->toStringConsult();
        }
        indexStart = indexStart->next;
        saveAmount--;
    }
}
