#include "Stream.h"

Stream::Stream(){
    this->__init__();
    this->cleanFiles();
}

int Stream::lastLine(QString filename)
{
    int lastLine = 0;
    QString data = "";
    QFile file(filename);
    QTextStream in (&file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<"file not opened"<<endl;
    else
    {
        do
        {
            data = in.readLine();
            lastLine++;
        }while(data != "");
    }
    return lastLine - 1;
}

QVector<QString> Stream::initArray(QString filename)
{
    QString data;
    QFile file(filename);
    QVector<QString> array;
    int lastLine = this->lastLine(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "file not opened";
    else
    {
        QTextStream in (&file);
        for(int i = 0; i < lastLine ; i++)
        {
            data = in.readLine();
            array.insert(i, data);
        }
    }

    file.close();
    return array;
}

QString Stream::randomOutput(QVector<QString> array, FileNameTxt name)
{
    switch(name)
    {
    case BoyNamesTxt: return randomOutputAux(array, rangeBoyNames[0], rangeBoyNames[1]);
    case GirlNamesTxt: return randomOutputAux(array, rangeGirlNames[0], rangeGirlNames[1]);
    case LastNamesTxt: return randomOutputAux(array, rangeLastNames[0], rangeLastNames[1]);
    case CountriesTxt: return randomOutputAux(array, rangeCountries[0], rangeCountries[1]);
    case ReligionsTxt: return randomOutputAux(array, rangeReligions[0], rangeReligions[1]);
    case ProfessionsTxt: return randomOutputAux(array, rangeProfession[0], rangeProfession[1]);
    case SportsTxt: return randomOutputAux(array, rangeSports[0], rangeSports[1]);
    }
    return "Invalido";
}

QString Stream::randomOutputAux(QVector<QString> array, int indexStart, int indexEnd)
 {
     if (indexStart == 0 && indexEnd == 0)
     {
         int lineNumber = static_cast<int>(QRandomGenerator::global()->generate() % unsigned (array.length()));
         return array.at(lineNumber);
     }
     else if (indexStart <= array.length() && indexEnd <= array.length() && indexStart < indexEnd)
     {
          int lineNumber = static_cast<int>(QRandomGenerator::global()->generate() % unsigned (indexEnd-indexStart) + unsigned (indexStart));
          return array.at(lineNumber);
     }
     qDebug()<< "Invalido";
     return "Invalido";
 }

 void Stream::__init__()
 {
     this->arrayBoyNames = this->initArray(":/Text/TextDocs/FirstNamesMale.txt");
     this->arrayGirlNames = this->initArray(":/Text/TextDocs/FirstNamesFemale.txt");
     this->arrayProfessions = this->initArray(":/Text/TextDocs/Profesions.txt");
     this->arrayLastNames = this->initArray(":/Text/TextDocs/LastNames.txt");
     this->arrayReligions = this->initArray(":/Text/TextDocs/Religions.txt");
     this->arraySports = this->initArray(":/Text/TextDocs/Sports.txt");
     this->arrayCountries = this->initArray(":/Text/TextDocs/Countries.txt");
 }

 void Stream::writeWorld(QString string)
 {
     //QFile file("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\World.txt");
     QFile file("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\World.txt");
     if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
     {
         QTextStream stream(&file);
         stream << string << endl;
     }
     else
         qDebug() << "file not opened";
     file.close();

 }

 void Stream::writeSalvation(QString string)
 {


     //QFile file("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\SalvationLog.txt");
     QFile file("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\SalvationLog.txt");
     if (file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QTextStream stream(&file);
         stream << string << endl;
     }
     else
         qDebug() << "file not opened";
     file.close();
     this->sendMail("Salvaciones","Hola señor Thanos me la pele", "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\SalvationLog.txt");
 }

 void Stream::writeDeath(QString string)
 {
     //QFile file("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\DeathLog.txt");
     QFile file("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\DeathLog.txt");
     if (file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
         QTextStream stream(&file);
         stream << string << endl;
     }
     else
         qDebug() << "file not opened";
     file.close();
     this->sendMail("Muertes","Hola señor Thanos aqui reportando casual la aniquilacion de la humanidad, saludos", "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\DeathLog.txt");
 }

 void Stream::writeEvent(QString string, AlgorithmNameTxt name)
 {
     QString fileName;
     switch(name)
     {
     case ThanosTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Thanos.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Thanos.txt";
         break;
     case NebulaTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Nebula.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Nebula.txt";
         break;
     case EbonyMawTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\EbonyMaw.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\EbonyMaw.txt";
         break;
     case BlackDwarfTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\BlackDwarf.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\BlackDwarf.txt";
         break;
     case CorvusGlaiveTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\CorvusGlaive.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\CorvusGlaive.txt";
         break;
     case MidnightTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Midnight.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Midnight.txt";
         break;
     case ThorTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Thor.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Thor.txt";
         break;
     case IronManTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\IronMan.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\IronMan.txt";
         break;
     case AntManTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\AntMan.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\AntMan.txt";
         break;
     case SpiderManTxt:
         fileName  = "D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\SpiderMan.txt";
         //fileName  = "C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\SpiderMan.txt";
         break;
     }
     QFile file(fileName);
     if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
     {
         QTextStream stream(&file);
         stream << string << endl;
     }
     else
         qDebug() << "file not opened";
     file.close();
 }

void Stream::writeTree(QString string)
{
    //QFile file("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Tree.txt");
    QFile file("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Tree.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << string << endl;
    }
    else
        qDebug() << "file not opened";
    file.close();
}

void Stream::cleanFiles()
{
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Thanos.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Nebula.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\EbonyMaw.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\BlackDwarf.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\CorvusGlaive.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Midnight.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\Thor.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\IronMan.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\AntMan.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\SpiderMan.txt");
//    cleanFilesAux("C:\\Users\\asus\\Desktop\\Avengers Tree Game\\Logs\\World.txt");

    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Thanos.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Nebula.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\EbonyMaw.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\BlackDwarf.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\CorvusGlaive.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Midnight.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\Thor.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\IronMan.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\AntMan.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\SpiderMan.txt");
    cleanFilesAux("D:\\Qt\\Projects\\Avengers Tree Game\\Logs\\World.txt");
}

void Stream::cleanFilesAux(QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;
    else
        qDebug() << "file not opened";
    file.close();
}

void Stream::sendMail(QString topic, QString content, QString path)
{
    QList <QString> listPath;
    listPath.append(path);
    Smtp * smtp = new Smtp("ale.garciy@gmail.com","3minicute3","smtp.gmail.com");
    smtp->sendMail("ale.garciy@gmail.com","ale.garciy@gmail.com", topic,content,listPath);
}
