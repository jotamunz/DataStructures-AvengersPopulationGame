#include "judgmentform.h"
#include "ui_judgmentform.h"

JudgmentForm::JudgmentForm(QWidget *parent, HashThanos * thanos) :
    QWidget(parent),
    ui(new Ui::JudgmentForm)
{
    ui->setupUi(this);
    this->thanos = thanos;
}

JudgmentForm::~JudgmentForm()
{
    delete ui;
}

void JudgmentForm::on_pushButton_clicked()
{
    if (this->ui->spinBoxFriends->text() != "")
        thanos->friendshipWeight = this->ui->spinBoxFriends->text().toInt();
    if (this->ui->spinBoxFamily->text() != "")
        thanos->familyWeight = this->ui->spinBoxFamily->text().toInt();
    if (this->ui->spinBoxAge->text() != "")
        thanos->ageWeights[this->ui->spinBoxAgeIndex->text().toInt()-1] = this->ui->spinBoxAge->text().toInt();
    if (this->ui->spinBoxSin->text() != "")
        thanos->sinsWeights[this->ui->spinBoxSinIndex->text().toInt()-1] = this->ui->spinBoxSin->text().toInt();
    if (this->ui->spinBoxVirtue->text() != "")
        thanos->virtueWeights[this->ui->spinBoxVirtueIndex->text().toInt()-1] = this->ui->spinBoxVirtue->text().toInt();
    if (this->ui->spinBoxTravel->text() != "")
        thanos->travelWeights = this->ui->spinBoxTravel->text().toInt();
    if (this->ui->spinBoxExercise->text() != "")
        thanos->exerciseWeight = this->ui->spinBoxExercise->text().toInt();
    this->hide();
}
