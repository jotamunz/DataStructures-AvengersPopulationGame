#include <HashSport.h>

void HashSport::addToArraySports(Person *person, Stream * stream)
{
    for(int i = 0; i < stream->arraySports.length(); i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if( person->sportsPracticed[j] != nullptr && stream->arraySports.at(i) == person->sportsPracticed[j])
            {
                this->arraySports[i].append(person);
            }
        }
    }
}
