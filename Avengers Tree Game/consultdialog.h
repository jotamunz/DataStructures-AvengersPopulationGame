#ifndef CONSULTDIALOG_H
#define CONSULTDIALOG_H

#include <QDialog>

namespace Ui {
class ConsultDialog;
}

class ConsultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConsultDialog(QWidget *parent = nullptr);
    ~ConsultDialog();

private:
    Ui::ConsultDialog *ui;
};

#endif // CONSULTDIALOG_H
