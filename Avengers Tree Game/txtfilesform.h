#ifndef TXTFILESFORM_H
#define TXTFILESFORM_H

#include <QWidget>
#include "Stream.h"

namespace Ui {
class TxtFilesForm;
}

class TxtFilesForm : public QWidget
{
    Q_OBJECT
    Stream * stream;


public:
    explicit TxtFilesForm(QWidget *parent = nullptr, Stream *stream = nullptr);
    ~TxtFilesForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TxtFilesForm *ui;
};

#endif // TXTFILESFORM_H
