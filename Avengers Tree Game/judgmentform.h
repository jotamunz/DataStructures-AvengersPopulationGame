#ifndef JUDGMENTFORM_H
#define JUDGMENTFORM_H

#include <QWidget>
#include "HashThanos.h"

namespace Ui {
class JudgmentForm;
}

class JudgmentForm : public QWidget
{
    Q_OBJECT
    HashThanos * thanos;

public:
    explicit JudgmentForm(QWidget *parent = nullptr, HashThanos * thanos = nullptr);
    ~JudgmentForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::JudgmentForm *ui;
};

#endif // JUDGMENTFORM_H
