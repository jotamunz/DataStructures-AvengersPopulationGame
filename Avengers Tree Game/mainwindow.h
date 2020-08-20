#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <World.h>
#include <QDebug>
#include "judgmentform.h"
#include "txtfilesform.h"
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    World * world;
    JudgmentForm * judgmentF;
    TxtFilesForm * txtFilesF;
    //GIFS
    QMovie * movie_IronMan;
    QMovie * movie_Spiderman;
    QMovie * movie_Thor;
    QMovie * movie_AntMan;
    QMovie * movie_BlackDwarf;
    QMovie * movie_CorvusGlaive;
    QMovie * movie_Midnight;
    QMovie * movie_Nebula;
    QMovie * movie_EbonyMaw;
    QMovie * movie_Thanos;
    QMovie * movie_ThanosWin;
    QMovie * movie_AvengersWin;
    //IMAGES
    QPixmap imageBackGround = QPixmap(":/Images/Images/Background.jpg");
    //HERO GIFS
    QPixmap gifIronMan = QPixmap(":/Images/Images/IronMan.gif");
    QPixmap gifSpiderMan = QPixmap(":/Images/Images/Midnight.gif");
    QPixmap gifAntMan = QPixmap(":/Images/Images/AntMan.gif");
    QPixmap gifThor = QPixmap(":/Images/Images/Thor.gif");
    QPixmap gifAvengersWin = QPixmap(":/Images/Images/AvengersWin.gif");
    //VILLIANS GIFS
    QPixmap gifThanos = QPixmap(":/Images/Images/Thor.gif");
    QPixmap gifCorvusGlaive = QPixmap(":/Images/Images/CorvusGlaive.gif");
    QPixmap gifNebula = QPixmap(":/Images/Images/Nebula.gif");
    QPixmap gifEbonyMaw = QPixmap(":/Images/Images/EbonyMaw.gif");
    QPixmap gifMidnight = QPixmap(":/Images/Images/Midnight.gif");
    QPixmap gifBlackDwarf = QPixmap(":/Images/Images/BlackDwarf.gif");
    QPixmap gifThanoWin = QPixmap(":/Images/Images/ThanosWin.gif");

public slots:
    void setImages();
    void setMovies();
    void setComboBox();

private slots:
    void on_pushButton_Consult_clicked();

    void on_pushButton_Accion_clicked();

    void on_actionJudgment_triggered();

    void on_actionTxtFiles_triggered();

    void on_pushButton_Generate_pressed();

    void on_pushButton_Generate_released();

    void on_pushButton_Info_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
