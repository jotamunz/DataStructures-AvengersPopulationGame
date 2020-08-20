#include "mainwindow.h"
#include <qdebug.h>
#include <QApplication>
#include "World.h"
#include "Stream.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
