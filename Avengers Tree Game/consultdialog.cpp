#include "consultdialog.h"
#include "ui_consultdialog.h"

ConsultDialog::ConsultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsultDialog)
{
    ui->setupUi(this);
}

ConsultDialog::~ConsultDialog()
{
    delete ui;
}
