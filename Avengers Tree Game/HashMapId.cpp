#include <HashMapId.h>

HashMapId::HashMapId(){
    this->initArrayRandom();
}

int HashMapId::cuentaDigitos(int number)
{
    if(number < 10)
        return 1;
    else
        return 1 + cuentaDigitos(number/10);
}

void HashMapId::hashRandom(int id)
{
    int digitQuantity = cuentaDigitos(id);
    QString idString = QString::number(id);

    if(digitQuantity < 6)
    {
        this->coordenateRandom.x = 0;
        this->coordenateRandom.y = 0;
    }
    else if(digitQuantity == 6 )
    {
        this->coordenateRandom.x = 0;
        this->coordenateRandom.y = idString.at(0).digitValue();

    }
    else
    {
        this->coordenateRandom.x = idString.at(0).digitValue();
        this->coordenateRandom.y = idString.at(1).digitValue();
    }
}

void HashMapId::initArrayRandom()
{
    for(int i = 0; i < 10; i++) // filas
    {
        for(int j = 0; j < 10; j++) // columnas
        {
            arrayRandom * array = new arrayRandom();
            for(int k = 0; k < 100000; k++) // contenido
                array->arrayRandom[k] = -1;
            this->hashMapRandom[i][j] = array;
        }
    }
}

bool HashMapId::addHashRandom(int id)
{
    int index = 0;
    this->hashRandom(id);

    while(hashMapRandom[coordenateRandom.y][coordenateRandom.x]->arrayRandom[index] != -1)
    {
        if(hashMapRandom[coordenateRandom.y][coordenateRandom.x]->arrayRandom[index] == id)
            return false;
        index ++;
    }
    hashMapRandom[coordenateRandom.y][coordenateRandom.x]->arrayRandom[index] = id;
    return true;
}

int HashMapId::getRandom()
{
    int random = 0;
    do
    {
         random = static_cast<int>(QRandomGenerator::global()->generate() % 10000000); //10000000
    }while(addHashRandom(random) == false);

    return random;
}
