#include <Person.h>

static int CURRENT_YEAR = 2019;
static int OLDEST_AGE = 99;

Person::Person(Stream* _stream, HashMapId* _hashMapId)
{
    this->stream = _stream;
    this->id = _hashMapId->getRandom();
    this->gender = generateGender();
    this->name = generateName();
    this->lastName = stream->randomOutput(stream->arrayLastNames, LastNamesTxt);
    this->religion = stream->randomOutput(stream->arrayReligions, ReligionsTxt);
    this->profession = stream->randomOutput(stream->arrayProfessions, ProfessionsTxt);
    this->birthDate = generateBirthDate();
    this->age = (CURRENT_YEAR - birthDate->year);
    this->ageGroup = generateAgeGroup();
    this->maritalStatus = generateMaritalStatus();
    this->weeklyExercise = static_cast<int>(QRandomGenerator::global()->generate() % 7 + 1);
    this->generateLivingLocation();
    this->generateSportsPracticed();
    this->generateVisitedCountries();
    this->initSinsAndVirtues();
    this->initFamilyAndFriends();
}

Gender Person::generateGender()
{
    if (QRandomGenerator::global()->generate() % (100) < 50)
        return Male;
    else
        return Female;
}

QString Person::generateName()
{
    if (gender == Male)
        return stream->randomOutput(stream->arrayBoyNames, BoyNamesTxt);
    else
        return stream->randomOutput(stream->arrayGirlNames, GirlNamesTxt);
}

Date* Person::generateBirthDate()
{
    int year = static_cast<int>(QRandomGenerator::global()->generate() % (unsigned (CURRENT_YEAR+1) - unsigned (CURRENT_YEAR - OLDEST_AGE)) + unsigned (CURRENT_YEAR - OLDEST_AGE));
    Month month = static_cast<Month>(QRandomGenerator::global()->generate() % (unsigned (12)) + unsigned (1));
    int day;
    if (month == February)
        day = static_cast<int>(QRandomGenerator::global()->generate() % (unsigned (28)) + unsigned (1));
    else if (month == January || month == March || month == May || month == July || month == August || month == October || month == December)
        day = static_cast<int>(QRandomGenerator::global()->generate() % (unsigned (31)) + unsigned (1));
    else
        day = static_cast<int>(QRandomGenerator::global()->generate() % (unsigned (30)) + unsigned (1));
    return new Date(year, month, day);
}

AgeGroup Person::generateAgeGroup()
{
    if (age <= 1)
        return Infant;
    else if (age <= 4)
        return Preschool;
    else if (age <= 10)
        return School;
    else if (age <= 14)
        return Puberty;
    else if (age <= 19)
        return Teen;
    else if (age <= 24)
        return Young;
    else if (age <= 34)
        return YoungAdult;
    else if (age <= 64)
        return MatureAdult;
    else
        return Elderly;
}

MaritalStatus Person::generateMaritalStatus()
{
    if (ageGroup >= Young)
    {
        unsigned int rand = QRandomGenerator::global()->generate() % (100);
        if (rand < 10)
            return Single;
        else if (rand < 90)
            return Married;
        else
            return Divorced;
    }
    else
        return Single;
}

void Person::initSinsAndVirtues()
{
    for (int i = 0; i < 7; i++)
    {
        this->sins[i] = new Sin(static_cast<SinName>(i));
        this->virtues[i] = new Virtue(static_cast<VirtueName>(i));
    }
}

void Person::initFamilyAndFriends()
{
    this->parents[0] = nullptr;
    this->parents[1] = nullptr;
    for (int i = 0; i < 4; i++)
        this->children[i] = nullptr;
    for (int i = 0; i < 50; i++)
        this->friends[i] = nullptr;
}

void Person::generateLivingLocation()
{
    this->livingLocation = stream->randomOutput(stream->arrayCountries, CountriesTxt);
    QStringList livingLocationTemp = livingLocation.split(',');
    this->livingContinent = livingLocationTemp.value(0);
    this->livingCountry = livingLocationTemp.value(1);
}

void Person::generateSportsPracticed()
{
    for (int i = 0; i < 3; i++)
        this->sportsPracticed[i] = this->stream->randomOutput(stream->arraySports, SportsTxt);
}

void Person::generateVisitedCountries()
{
    unsigned int rand = QRandomGenerator::global()->generate() % (100);
    int countryAmount;
    if (rand < 30)
        countryAmount = rand%3;
    else if (rand < 55)
        countryAmount = rand%9 + 2;
    else if (rand < 75)
        countryAmount = rand%6 + 10;
    else if (rand < 90)
        countryAmount = rand%11 + 15;
    else
        countryAmount = rand%26 + 25;
    if (countryAmount > (stream->rangeCountries[1] - stream->rangeCountries[0] - 1))
        countryAmount = (stream->rangeCountries[1] - stream->rangeCountries[0] - 1);
    for (int i = 0; i < countryAmount; i++)
    {
        QString country;
        do
        {
            country = this->stream->randomOutput(stream->arrayCountries, CountriesTxt).split(',').value(1);
        } while(countryInArray(country) || country == this->livingCountry);
        this->visitedCountries[i] = country;
    }
}

bool Person::countryInArray(QString country)
{
    for (int i = 0; i < 50; i++)
    {
        if (visitedCountries[i] != nullptr)
        {
            if (visitedCountries[i] == country)
                return true;
        }
        else break;
    }
    return false;
}

bool Person::friendInArray(Person* person)
{
    for (int i = 0; i < 50; i++)
    {
        if (friends[i] != nullptr)
        {
            if (friends[i] == person)
                return true;
        }
        else break;
    }
    return false;
}

bool Person::isEmptyFriends()
{
    return friends[0] == nullptr;
}

QString Person::toString()
{
    QString str = "ID: " + QVariant(this->id).toString() + "\n";
    str += "Name: " + this->name + " " + this->lastName + "\n";
    str += "Gender: " + this->genderString(this->gender) + "\n";
    str += "Age: " + QVariant(this->age).toString() + " " + this->ageGroupString(this->ageGroup) + "\n";
    str += "Year: " + QVariant(this->birthDate->year).toString() + " Month: " + QVariant(this->birthDate->month).toString() + " Day: " + QVariant(this->birthDate->day).toString() + "\n";
    str += "Marital Status: " + this->maritalStatusString(this->maritalStatus) + "\n";
    str += "Religion: " + this->religion + " Profession: " + this->profession + "\n";
    str += "Continent: " + this->livingContinent + " Country: " + this->livingCountry + "\n" ;
    str += "Visited Countries: ";
    for (int i = 0; i < 50; i++)
    {
        if (visitedCountries[i] != nullptr)
            str += QString::number(i) + "." + visitedCountries[i] + " ";
        else break;
    }
    str += "\n";
    str += "Weekly Exercise: " + QVariant(this->weeklyExercise).toString() + "\n";
    str += "Sports: " + this->sportsPracticed[0] + " " + this->sportsPracticed[1] + " " +  this->sportsPracticed[2] + "\n";
    str += "State: " + this->stateString(this->state) + "\n";
    if(this->parents[0] != nullptr)
        str += "Parents: " + this->parents[0]->name + "[" + QVariant(this->parents[0]->id).toString() + "]" + " & " + this->parents[1]->name + "[" + QVariant(this->parents[1]->id).toString() + "]"+ "\n";
    else
        str += "Parents: None \n";
    if(this->spouse != nullptr)
       str += "Spouse: " + this->spouse->name +"[" + QVariant(this->spouse->id).toString() + "] \n";
    else
        str += "Spouse: none \n";
    str += "Friends: ";
    for (int i = 0; i < 50; i++)
    {
        if (friends[i] != nullptr)
            str += QString::number(i) + "." + friends[i]->name + "[" + QVariant(friends[i]->id).toString() + "] ";
        else break;
    }
    str += "\n";
    str += "Children: ";
    if(this->children[0] == nullptr )
        str += "none ";
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (this->children[i] != nullptr)
                str += children[i]->name + "[" + QVariant(children[i]->id).toString() + "] ";
            else break;
        }
    }
    str += "\n";
    str += "Sins: ";
    for(int i = 0; i < 7; i++)
    {
        str += this->sins[i]->getSinString(this->sins[i]->name) + "[" + QVariant(this->sins[i]->amount).toString() + "]";
    }
    str += "Total[" + QVariant(this->totalSins).toString() + "]";
    str += "\n";
    str += "Virtues: ";
    for(int i = 0; i < 7; i++)
    {
        str += this->virtues[i]->getVirtueString(this->virtues[i]->name) + "[" + QVariant(this->virtues[i]->amount).toString() + "]";
    }
    str += "Total[" + QVariant(this->totalVirtues).toString() + "]";
    str += "\n";
    QDateTime time = time.currentDateTime();
    str += time.toString();
    str += "\n";
    return str;
}

QString Person::toStringConsult()
{
    QString str = "ID: " + QVariant(this->id).toString() + "\t";
    str += "Name: " + this->name + " " + this->lastName + "\t";
    str += "Gender: " + this->genderString(this->gender) + "\t";
    str += "Age: " + QVariant(this->age).toString() + " " + this->ageGroupString(this->ageGroup) + "\t";
    str += "Year: " + QVariant(this->birthDate->year).toString() + " Month: " + QVariant(this->birthDate->month).toString() + " Day: " + QVariant(this->birthDate->day).toString() + "\t";
    str += "Marital Status: " + this->maritalStatusString(this->maritalStatus) + "\t";
    str += "Religion: " + this->religion + " Profession: " + this->profession + "\t";
    str += "Continent: " + this->livingContinent + " Country: " + this->livingCountry + "\t" ;
    str += "Visited Countries: ";
    for (int i = 0; i < 50; i++)
    {
        if (visitedCountries[i] != nullptr)
            str += QString::number(i) + "." + visitedCountries[i] + " ";
        else break;
    }
    str += "\t";
    str += "Weekly Exercise: " + QVariant(this->weeklyExercise).toString() + "\t";
    str += "Sports: " + this->sportsPracticed[0] + " " + this->sportsPracticed[1] + " " +  this->sportsPracticed[2] + "\t";
    str += "State: " + this->stateString(this->state) + "\t";
    if(this->parents[0] != nullptr)
        str += "Parents: " + this->parents[0]->name + "[" + QVariant(this->parents[0]->id).toString() + "]" + " & " + this->parents[1]->name + "[" + QVariant(this->parents[1]->id).toString() + "]"+ "\t";
    else
        str += "Parents: None \t";
    if(this->spouse != nullptr)
       str += "Spouse: " + this->spouse->name +"[" + QVariant(this->spouse->id).toString() + "] \t";
    else
        str += "Spouse: none \t";
    str += "Friends: ";
    for (int i = 0; i < 50; i++)
    {
        if (friends[i] != nullptr)
            str += QString::number(i) + "." + friends[i]->name + "[" + QVariant(friends[i]->id).toString() + "] ";
        else break;
    }
    str += "\t";
    str += "Children: ";
    if(this->children[0] == nullptr )
        str += "none ";
    else
    {
        for (int i = 0; i < 4; i++)
        {
            if (this->children[i] != nullptr)
                str += children[i]->name + "[" + QVariant(children[i]->id).toString() + "] ";
            else break;
        }
    }
    str += "\t";
    str += "Sins: ";
    for(int i = 0; i < 7; i++)
    {
        str += this->sins[i]->getSinString(this->sins[i]->name) + "[" + QVariant(this->sins[i]->amount).toString() + "]";
    }
    str += "Total[" + QVariant(this->totalSins).toString() + "]";
    str += "\t";
    str += "Virtues: ";
    for(int i = 0; i < 7; i++)
    {
        str += this->virtues[i]->getVirtueString(this->virtues[i]->name) + "[" + QVariant(this->virtues[i]->amount).toString() + "]";
    }
    str += "Total[" + QVariant(this->totalVirtues).toString() + "]";
    str += "\t";
    QDateTime time = time.currentDateTime();
    str += time.toString();
    str += "\n";
    return str;
}

QString Person::ageGroupString(AgeGroup ageGroupValue)
{
    QString ageGroups[12] = {"Infant", "Preschool", "School", "Puberty", "Teen", "Young", "YoungAdult", "MatureAdult", "Elderly"};
    return ageGroups[ageGroupValue];
}

QString Person::genderString(Gender genderValue)
{
    QString genders[2] = {"Male", "Female"};
    return genders[genderValue];
}

QString Person::maritalStatusString(MaritalStatus statusValue)
{
    QString status[3] = {"Single", "Married", "Divorced"};
    return status[statusValue];
}

QString Person::stateString(State stateNumber)
{
    QString state[3] = {"Alive", "Dead", "Saved"};
    return state[stateNumber];
}



