#include <HashThanos.h>

static int CURRENT_YEAR = 2019;

HashThanos::HashThanos(DoubleList * list,Stream * stream)
{
    this->people = list;
    this->stream = stream;
}

int HashThanos::getFriendsAmount(Person * person)
{
    int amount = 0;
    for(int i = 0; i < 50 && person->friends[i] != nullptr; i++)
        amount ++;
    return amount * this->friendshipWeight;
}

int HashThanos::getfamilyAmount(Person * person)
{
    int amount = 0;
    for(int i = 0; i < 4 && person->children[i] != nullptr; i++)
        amount ++;
    return amount * this->familyWeight;
}

int HashThanos::getAgeAmount(Person * person)
{
    return this->ageWeights[person->ageGroup];
}

int HashThanos::getSinsAmount(Person * person)
{
    int amount = 0;
    for(int i = 0; i < 7; i++)
        amount += person->sins[i]->amount * this->sinsWeights[i];
    return amount;
}

int HashThanos::getVirtueAmount(Person * person)
{
    int amount = 0;
    for(int i = 0; i < 7; i++)
        amount += person->virtues[i]->amount * this->virtueWeights[i];
    return amount;
}

int HashThanos::getTravelAmount(Person * person)
{
    int amount = 0;
    for(int i = 0; i < 50 && person->visitedCountries[i] != nullptr; i++)
        amount ++;
    return amount * this->travelWeights;
}

int HashThanos::getExcerciseWeight(Person * person)
{
    return person->weeklyExercise * this->exerciseWeight;
}

void HashThanos::setTotalWeight(Person * person)
{
    int amount = 0;
    amount += this->getFriendsAmount(person);
    amount += this->getfamilyAmount(person);
    amount += this->getAgeAmount(person);
    amount -= this->getSinsAmount(person);
    amount += this->getVirtueAmount(person);
    amount += this->getTravelAmount(person);
    amount += this->getExcerciseWeight(person);
    person->lifeScore = amount;
}

void HashThanos::indexPersonTotals()
{
    Node * temp = this->people->first;

    while(temp != nullptr)
    {
        this->setTotalWeight(temp->person);
        this->Totals.append(temp->person);
        temp = temp->next;
    }
    this->selectSortThanos();
}

void HashThanos::selectSortThanos()
{
    QString str;
    for(int i = 0; i < this->Totals.length(); i ++)
    {
        str = " ";
        int min = i;

        for(int j = i; j < this->Totals.length(); j++)
        {
            if(Totals[j]->lifeScore < Totals[min]->lifeScore)
                min = j;
        }
        if(i != min)
        {
            Person* temp = this->Totals[i];
            this->Totals[i] = this->Totals[min];
            this->Totals[min] = temp;
        }
    }
}

int HashThanos::getIndexYear(int year)
{
    return CURRENT_YEAR-year;
}

void HashThanos::indexHashThanos()
{
    QString str;
    int levelAmount = Totals.length()/10;
    int personIndex = 0;
    for(int j = 0; j < 9; j++) // level
    {
        for(int i = 0; i < levelAmount; i++) // amount of persons
        {
            this->thanosNaughtyList[Totals[personIndex]->age][j].append(Totals[personIndex]);
            personIndex++;
        }
    }
    for(int i = personIndex; i < Totals.length(); i++)
    {
        this->thanosNaughtyList[Totals[personIndex]->age][9].append(Totals[personIndex]); // el resto va a max
        personIndex++;
    }
}

QStringList HashThanos::doJustice(int year, int i)
{
    //level (0-9)
    QStringList stringList;
    QString deathString = "";
        for(int k = 0;this->thanosNaughtyList[this->getIndexYear(year)][i].isEmpty() == false && k < this->thanosNaughtyList[this->getIndexYear(year)][i].length();k++)//QVECTOR
        {
            if(thanosNaughtyList[this->getIndexYear(year)][i].at(k) != nullptr && thanosNaughtyList[this->getIndexYear(year)][i].at(k)->state != Dead)
            {
                this->thanosNaughtyList[this->getIndexYear(year)][i].at(k)->state = Dead;
                deathString += "Level: "+ QVariant(i).toString()+" Thanos killed :" + this->thanosNaughtyList[this->getIndexYear(year)][i].at(k)->toStringConsult();
                stringList.append("ID: " + QVariant( thanosNaughtyList[this->getIndexYear(year)][i].at(k)->id).toString() + " Name: " + thanosNaughtyList[this->getIndexYear(year)][i].at(k)->name + " killed");
            }
        }

    this->stream->writeDeath(deathString);
    this->stream->writeEvent(deathString, ThanosTxt);
    return stringList;
}

QStringList HashThanos::doJustice_aux(int year, int i)
{
    //level (0-9)
    QStringList stringList;
    QString deathString = "";
        for(int k = 0;this->thanosNaughtyList[year][i].isEmpty() == false && k < this->thanosNaughtyList[year][i].length();k++)//QVECTOR
        {
            if(thanosNaughtyList[year][i].at(k) != nullptr && thanosNaughtyList[year][i].at(k)->state != Dead)
            {
                this->thanosNaughtyList[year][i].at(k)->state = Dead;
                deathString += "Level: "+ QVariant(i).toString()+" Thanos killed :" + this->thanosNaughtyList[year][i].at(k)->toStringConsult();
                stringList.append("ID: " + QVariant( thanosNaughtyList[year][i].at(k)->id).toString() + " Name: " + thanosNaughtyList[year][i].at(k)->name + " killed");
            }
         }

    this->stream->writeDeath(deathString);
    this->stream->writeEvent(deathString, ThanosTxt);
    return stringList;
}


QStringList HashThanos::doJusticeLevel(int level)
{
    QStringList stringList;
    for(int i = 0; i < 100; i++)
    {
        stringList += this->doJustice_aux(i, level);
    }
    return stringList;
}

QStringList HashThanos::doJusticeYear(int year)
{
    QStringList stringList;
    for(int i = 0; i < 10; i++)
    {
        stringList += this->doJustice_aux(this->getIndexYear(year), i);
    }
    return stringList;
}

void HashThanos::clean()
{
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 10; j++)
            this->thanosNaughtyList[i][j].clear();
}
