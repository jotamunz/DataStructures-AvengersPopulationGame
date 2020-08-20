#include <HashMapFamily.h>

//----------------------------------------MARRIED--------------------------------------------

void HashMapFamily::addToArraysMarried(Person* person)
{
    if(person->ageGroup == Young && person->maritalStatus == Married)
        this->arrayYoung.append(person);
    else if(person->ageGroup == YoungAdult && person->maritalStatus == Married)
        this->arrayYoungAdult.append(person);
    else if(person->ageGroup == MatureAdult && person->maritalStatus == Married)
        this->arrayMatureAdult.append(person);
    else if(person->ageGroup == Elderly && person->maritalStatus == Married)
        this->arrayElderly.append(person);
}

void HashMapFamily::MarryPersons(Stream * stream)
{
    //Same age
    this->MarryPersonSameAge(this->arrayYoung);
    this->MarryPersonSameAge(this->arrayYoungAdult);
    this->MarryPersonSameAge(this->arrayMatureAdult);
    this->MarryPersonSameAge(this->arrayElderly);
    //One level higher
    this->MarryPersonOlder(this->arrayYoung,this->arrayYoungAdult);
    this->MarryPersonOlder(this->arrayYoungAdult,this->arrayMatureAdult);
    this->MarryPersonOlder(this->arrayMatureAdult,this->arrayElderly);
    //Solteros
    this->DeclareSingle(this->arrayYoung);
    this->DeclareSingle(this->arrayYoungAdult);
    this->DeclareSingle(this->arrayMatureAdult);
    this->DeclareSingle(this->arrayElderly);
    //Make Families
    this->makeFamilySameAge(stream);
    //Empty
    this->arrayYoung.empty();
    this->arrayYoungAdult.empty();
    this->arrayMatureAdult.empty();
    this->arrayElderly.empty();
}

void HashMapFamily::MarryPersonSameAge(QVector<Person*> array)
{
    for(int i = 0; i < array.length(); i++) //recorre toda la lista
    {
       if(array.at(i)->spouse == nullptr)
       {
           for(int j = i; j < array.length(); j++)//buscando esposos
           {

               if(array.at(i)->spouse == nullptr && array.at(j)->spouse == nullptr && array.at(j)->gender != array.at(i)->gender)
               {
                   array.at(i)->spouse = array.at(j);
                   array.at(j)->spouse = array.at(i);
               }
           }
       }
    }
}

void HashMapFamily::MarryPersonOlder(QVector<Person*> arrayYounger,QVector<Person*> arrayOlder)
{
    for(int i = 0; i <  arrayYounger.length(); i++) //recorre toda la lista younger
    {
       if( arrayYounger.at(i)->spouse == nullptr)
       {
           for(int j = 0; j < arrayOlder.length(); j++)//buscando esposos viejos
           {

               if(arrayYounger.at(i)->spouse == nullptr && arrayOlder.at(j)->spouse == nullptr && arrayOlder.at(j)->gender != arrayYounger.at(i)->gender)
               {
                   arrayYounger.at(i)->spouse = arrayOlder.at(j);
                   arrayOlder.at(j)->spouse = arrayYounger.at(i);
               }
           }
       }
    }
}

void HashMapFamily::DeclareSingle(QVector<Person*> array)
{
    for(int i = 0; i < array.length(); i++) //recorre toda la lista
    {
        if(array.at(i)->spouse == nullptr)
        {
            array.at(i)->maritalStatus = Single;
        }
    }
}

//--------------------------------------CHILDREN--------------------------------------------

void HashMapFamily::hashChild( Person * person, Stream * stream, int ageGroup)
{
    this->coordenatesChild.x = ageGroup;
    this->coordenatesChild.y = this->hashChildCountry (person, stream);
}

void HashMapFamily::addToHashChildren(Person * person, Stream * stream)
{
    if(person->ageGroup != Elderly)
    {
        this->coordenatesChild.x = person->ageGroup;
        this->coordenatesChild.y = this->hashChildCountry (person, stream);
        this->hashMapChilds[coordenatesChild.y][coordenatesChild.x].append(person);
    }
}

int HashMapFamily::hashChildCountry(Person * person, Stream* stream)
{
    for(int i = 0; i < stream->arrayCountries.length(); i++)
    {
        if(stream->arrayCountries.at(i).split(',')[1] == person->livingCountry)
            return i;

    }
    return -1;
}

//--------------------------------------CHILDREN--------------------------------------------

void HashMapFamily::makeFamilySameAge(Stream * stream)
{
    //YOUNG
    for(int i = 0; i < this->arrayYoung.length(); i++)
    {
        if(arrayYoung.at(i)->spouse != nullptr && arrayYoung.at(i)->spouse->ageGroup == arrayYoung.at(i)->ageGroup)
        {
            findChildrens(this->arrayYoung.at(i),stream,Infant);
            findChildrens(this->arrayYoung.at(i),stream,Preschool);
        }
        else if(arrayYoung.at(i)->spouse != nullptr)
        {
            findChildrens(this->arrayYoung.at(i),stream,Infant);
            findChildrens(this->arrayYoung.at(i),stream,Preschool);
            findChildrens(this->arrayYoung.at(i),stream,School);
            findChildrens(this->arrayYoung.at(i),stream,Puberty);
        }
    }

    //YOUNG-ADULT
    for(int i = 0; i < this->arrayYoungAdult.length(); i++)
    {
        if(arrayYoungAdult.at(i)->spouse != nullptr && arrayYoungAdult.at(i)->spouse->ageGroup == arrayYoungAdult.at(i)->ageGroup)
        {
            findChildrens(this->arrayYoungAdult.at(i),stream,Infant);
            findChildrens(this->arrayYoungAdult.at(i),stream,Preschool);
            findChildrens(this->arrayYoungAdult.at(i),stream,School);
            findChildrens(this->arrayYoungAdult.at(i),stream,Puberty);
        }
        else if(arrayYoungAdult.at(i)->spouse != nullptr)
        {
            findChildrens(this->arrayYoungAdult.at(i),stream,Infant);
            findChildrens(this->arrayYoungAdult.at(i),stream,Preschool);
            findChildrens(this->arrayYoungAdult.at(i),stream,School);
            findChildrens(this->arrayYoungAdult.at(i),stream,Puberty);
            findChildrens(this->arrayYoungAdult.at(i),stream,Teen);
            findChildrens(this->arrayYoungAdult.at(i),stream,Young);
        }
    }

    //MATURE-ADULT
    for(int i = 0; i < this->arrayMatureAdult.length(); i++)
    {
        if(arrayMatureAdult.at(i)->spouse != nullptr && arrayMatureAdult.at(i)->spouse->ageGroup == arrayMatureAdult.at(i)->ageGroup)
        {
            findChildrens(this->arrayMatureAdult.at(i),stream,Teen);
            findChildrens(this->arrayMatureAdult.at(i),stream,Young);
            findChildrens(this->arrayMatureAdult.at(i),stream,YoungAdult);
        }
        else if(arrayMatureAdult.at(i)->spouse != nullptr)
        {
            findChildrens(this->arrayMatureAdult.at(i),stream,Teen);
            findChildrens(this->arrayMatureAdult.at(i),stream,Young);
            findChildrens(this->arrayMatureAdult.at(i),stream,YoungAdult);
        }
    }
    //ELDERLY
    for(int i = 0; i < this->arrayElderly.length(); i++)
    {
        findChildrens(this->arrayElderly.at(i),stream,YoungAdult);
        findChildrens(this->arrayElderly.at(i),stream,MatureAdult);
    }

}

void HashMapFamily::findChildrens(Person * person, Stream * stream, int ageGroup)
{
    this->hashChild(person,stream,ageGroup);
    for(int i = 0; i < this->hashMapChilds[coordenatesChild.y][coordenatesChild.x].length() && person->children[3] == nullptr && person->spouse != nullptr ; i++)
    {
        if( hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->hasParent == false && ((hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->livingCountry == person->livingCountry || hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->livingCountry == person->spouse->livingCountry) && (hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->lastName == person->lastName  || hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->lastName == person->spouse->lastName)))
        {
            for(int j = 0; j<4 ; j++)
            {
                if(person->children[j] == nullptr)
                {
                    person->spouse->children[j] = hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i);
                    person->children[j] = hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i);
                    hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->hasParent = true;
                    hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->parents[0] = person;
                    hashMapChilds[coordenatesChild.y][coordenatesChild.x].at(i)->parents[1] = person->spouse;
                    break;
                }
            }
        }
    }
}

