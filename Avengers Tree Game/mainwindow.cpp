#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->world = new World();
    this->judgmentF = new JudgmentForm(nullptr, world->hashThanos);
    this->txtFilesF = new TxtFilesForm(nullptr, world->stream);
    this->setImages();
    this->setMovies();
    this->setComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImages()
{
    ui->label_background->setPixmap(imageBackGround.scaled(1920,1080));
}

void MainWindow::setMovies()
{
    this->movie_IronMan =       new QMovie(":/Images/Images/IronMan.gif");
    this->movie_Spiderman =     new QMovie(":/Images/Images/Spiderman.gif");
    this->movie_Thor =          new QMovie(":/Images/Images/Thor.gif");
    this->movie_AntMan =        new QMovie(":/Images/Images/AntMan.gif");
    this->movie_BlackDwarf =    new QMovie("::/Images/Images/BlackDwarf.gif");
    this->movie_CorvusGlaive =  new QMovie(":/Images/Images/CorvusGlaive.gif");
    this->movie_Midnight =      new QMovie(":/Images/Images/Midnight.gif");
    this->movie_Nebula =        new QMovie(":/Images/Images/Nebula.gif");
    this->movie_EbonyMaw =      new QMovie(":/Images/Images/EbonyMaw.gif");
    this->movie_Thanos =        new QMovie(":/Images/Images/Thanos.gif");
    this->movie_ThanosWin =     new QMovie(":/Images/Images/ThanosWin.gif");
    this->movie_AvengersWin =   new QMovie(":/Images/Images/AvengersWin.gif");

}


void MainWindow::setComboBox()
{
    ui->comboBox_Consults->addItem("Persona");  // index 0
    ui->comboBox_Consults->addItem("Familia");  // index 1
    ui->comboBox_Consults->addItem("Amigos");   // index 2
    ui->comboBox_Consults->addItem("Deporte");  // index 3
    ui->comboBox_Consults->addItem("Vivos");    // index 4
    ui->comboBox_Consults->addItem("Muertos");  // index 5
    ui->comboBox_Consults->addItem("Salvados"); // index 6

    ui->comboBox_Accion->addItem("Iron Man");      // index 0
    ui->comboBox_Accion->addItem("Spiderman");     // index 1
    ui->comboBox_Accion->addItem("Thor");          // index 2
    ui->comboBox_Accion->addItem("Ant Man");       // index 3
    ui->comboBox_Accion->addItem("Corvus Glaive"); // index 4
    ui->comboBox_Accion->addItem("Midnight");      // index 5
    ui->comboBox_Accion->addItem("Black Dwarf");   // index 6
    ui->comboBox_Accion->addItem("Ebony Maw");     // index 7
    ui->comboBox_Accion->addItem("Nebula");        // index 8
    ui->comboBox_Accion->addItem("Thanos");        // index 9

    ui->comboBox_Generate->addItem("Personas");
    ui->comboBox_Generate->addItem("Pecados");
    ui->comboBox_Generate->addItem("Virtudes");

    ui->pushButton_Info->setCheckable(true);

}

void MainWindow::on_pushButton_Consult_clicked()
{
    this->ui->listWidget_Consult->clear();
    int index = this->ui->comboBox_Consults->currentIndex();
    if(index == 0)
    {
        int num = this->ui->spinBox_Consult->text().toInt();
        this->ui->listWidget_Consult->addItem(world->consultPerson(num));
    }
    else if (index == 1)
    {
        int num = this->ui->spinBox_Consult->text().toInt();
        QStringList temp = world->consultFamilyPerson_aux(num);
        for(int i = 0; i< temp.length(); i++)
           this->ui->listWidget_Consult->addItem(temp[i]);
    }
    else if (index == 2)
    {
       int num = this->ui->spinBox_Consult->text().toInt();
       world->consultFrindsChainPerson(num);
       for(int i = 0; i< world->infoList.length(); i++)
           this->ui->listWidget_Consult->addItem(world->infoList[i]);
    }
    else if (index == 3)
    {
        if (this->ui->lineEdit_Consult->text() != "")
        {
           QString string = this->ui->lineEdit_Consult->text();
           world->consultSport(string);
           for(int i = 0; i< world->infoList.length(); i++)
               this->ui->listWidget_Consult->addItem(world->infoList[i]);
        }
    }
    else if (index == 4)
    {
        world->consultPersonsAlive();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Consult->addItem(world->infoList[i]);
    }
    else if (index == 5)
    {
        world->consultPersonsDead();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Consult->addItem(world->infoList[i]);
    }
    else if (index == 6)
    {
        world->consultPersonsSaved();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Consult->addItem(world->infoList[i]);
    }
}

void MainWindow::on_pushButton_Accion_clicked()
{
    this->ui->listWidget_Accion->clear();
    int index =  this->ui->comboBox_Accion->currentIndex();

    if (index == 0)
    {
        world->IronMan();
        this->ui->label_GIFS->setMovie(this->movie_IronMan);
        this->ui->label_GIFS->show();
        this->movie_IronMan->start();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 1)
    {
        world->SpiderMan();
        this->ui->label_GIFS->setMovie(this->movie_Spiderman);
        this->ui->label_GIFS->show();
        this->movie_Spiderman->start();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 2)
    {
        world->Thor();
        this->ui->label_GIFS->setMovie(this->movie_Thor);
        this->ui->label_GIFS->show();
        this->movie_Thor->start();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 3)
    {
        this->ui->label_GIFS->setMovie(this->movie_AntMan);
        this->ui->label_GIFS->show();
        this->movie_AntMan->start();
        int num = this->ui->spinBox_Action1->text().toInt();
        world->AntMan(num);
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 4)
    {
        this->ui->label_GIFS->setMovie(this->movie_CorvusGlaive);
        this->ui->label_GIFS->show();
        this->movie_CorvusGlaive->start();
        world->CorvusGlaive();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 5)
    {
        this->ui->label_GIFS->setMovie(this->movie_Midnight);
        this->ui->label_GIFS->show();
        this->movie_Midnight->start();
        world->Midnight();
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 6)
    {
        if (this->ui->lineEdit_Action->text() != "")
        {
            this->ui->label_GIFS->setMovie(this->movie_BlackDwarf);
            this->ui->label_GIFS->show();
            this->movie_BlackDwarf->start();
            QString string = this->ui->lineEdit_Action->text();
            int num = this->ui->spinBox_Action1->text().toInt();
            world->BlackDwarf(string,num);
            for(int i = 0; i< world->infoList.length(); i++)
                this->ui->listWidget_Accion->addItem(world->infoList[i]);
        }
    }
    else if (index == 7)
    {
        this->ui->label_GIFS->setMovie(this->movie_EbonyMaw);
        this->ui->label_GIFS->show();
        this->movie_EbonyMaw->start();
        int num = this->ui->spinBox_Action1->text().toInt();
        world->EbonyMaw(num);
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 8)
    {
        this->ui->label_GIFS->setMovie(this->movie_Nebula);
        this->ui->label_GIFS->show();
        this->movie_Nebula->start();
        int num = this->ui->spinBox_Action1->text().toInt();
        world->Nebula(num);
        for(int i = 0; i< world->infoList.length(); i++)
            this->ui->listWidget_Accion->addItem(world->infoList[i]);
    }
    else if (index == 9)
    {
        this->ui->label_GIFS->setMovie(this->movie_Thanos);
        this->ui->label_GIFS->show();
        this->movie_Thanos->start();
        if (this->ui->spinBox_Action1->text().toInt() == -1 && this->ui->spinBox_Action2->text().toInt() == -1)
        {
            qDebug() << "Invalido";
        }
        else if (this->ui->spinBox_Action1->text().toInt() == -1)
        {
            int level = this->ui->spinBox_Action2->text().toInt();
            world->Thanos(-1, level);
            for(int i = 0; i< world->infoList.length(); i++)
                this->ui->listWidget_Accion->addItem(world->infoList[i]);
        }
        else if (this->ui->spinBox_Action2->text().toInt() == -1)
        {
            int year = this->ui->spinBox_Action1->text().toInt();
            world->Thanos(year, -1);
            for(int i = 0; i< world->infoList.length(); i++)
                this->ui->listWidget_Accion->addItem(world->infoList[i]);
        }
        else
        {
            int year = this->ui->spinBox_Action1->text().toInt();
            int level = this->ui->spinBox_Action2->text().toInt();
            world->Thanos(year, level);
            for(int i = 0; i< world->infoList.length(); i++)
                this->ui->listWidget_Accion->addItem(world->infoList[i]);
        }
    }
}


void MainWindow::on_actionJudgment_triggered()
{
    this->judgmentF->show();
}

void MainWindow::on_actionTxtFiles_triggered()
{
    this->txtFilesF->show();
}

void MainWindow::on_pushButton_Generate_pressed()
{
    int index =  this->ui->comboBox_Generate->currentIndex();
    if (index == 0)
    {
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Processing...");
    }
    else if (index == 1)
    {
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Processing...");
    }
    else if (index == 2)
    {
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Processing...");
    }
}

void MainWindow::on_pushButton_Generate_released()
{
    int index =  this->ui->comboBox_Generate->currentIndex();
    if (index == 0)
    {
        int num = this->ui->spinBox_Generate->text().toInt();
        world->createPeople(num);
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Success");
    }
    else if (index == 1)
    {
        world->setSins();
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Success");
    }
    else if (index == 2)
    {
        world->setVirtues();
        this->ui->listWidget_Generate->clear();
        this->ui->listWidget_Generate->addItem("Success");
    }
}

void MainWindow::on_pushButton_Info_clicked()
{
    if (world->consultWinningTeam())
    {
        this->ui->label_GIFS->setMovie(this->movie_AvengersWin);
        this->ui->label_GIFS->show();
        this->movie_AvengersWin->start();
        this->ui->listWidget_Winner->clear();
        this->ui->listWidget_Winner->addItem("WINNING TEAM: THE AVENGERS");
    }
    else
    {
        this->ui->label_GIFS->setMovie(this->movie_ThanosWin);
        this->ui->label_GIFS->show();
        this->movie_ThanosWin->start();
        this->ui->listWidget_Winner->clear();
        this->ui->listWidget_Winner->addItem("WINNING TEAM: THANOS ARMY");
    }
}
