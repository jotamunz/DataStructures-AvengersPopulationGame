#include "txtfilesform.h"
#include "ui_txtfilesform.h"

TxtFilesForm::TxtFilesForm(QWidget *parent, Stream *stream) :
    QWidget(parent),
    ui(new Ui::TxtFilesForm)
{
    ui->setupUi(this);
    this->stream = stream;
}

TxtFilesForm::~TxtFilesForm()
{
    delete ui;
}

void TxtFilesForm::on_pushButton_clicked()
{
    if (this->ui->spinBoxBoyStart->text() != "")
        stream->rangeBoyNames[0] = this->ui->spinBoxBoyStart->text().toInt();
    if (this->ui->spinBoxBoyEnd->text() != "")
        stream->rangeBoyNames[1] = this->ui->spinBoxBoyEnd->text().toInt();
    if (this->ui->spinBoxGirlStart->text() != "")
        stream->rangeGirlNames[0] = this->ui->spinBoxGirlStart->text().toInt();
    if (this->ui->spinBoxGirlEnd->text() != "")
        stream->rangeGirlNames[1] = this->ui->spinBoxGirlEnd->text().toInt();
    if (this->ui->spinBoxLastStart->text() != "")
        stream->rangeLastNames[0] = this->ui->spinBoxLastStart->text().toInt();
    if (this->ui->spinBoxLastEnd->text() != "")
        stream->rangeLastNames[1] = this->ui->spinBoxLastEnd->text().toInt();
    if (this->ui->spinBoxCountryStart->text() != "")
        stream->rangeCountries[0] = this->ui->spinBoxCountryStart->text().toInt();
    if (this->ui->spinBoxCountryEnd->text() != "")
        stream->rangeCountries[1] = this->ui->spinBoxCountryEnd->text().toInt();
    if (this->ui->spinBoxReligionStart->text() != "")
        stream->rangeReligions[0] = this->ui->spinBoxReligionStart->text().toInt();
    if (this->ui->spinBoxReligionEnd->text() != "")
        stream->rangeReligions[1] = this->ui->spinBoxReligionEnd->text().toInt();
    if (this->ui->spinBoxProfessionStart->text() != "")
        stream->rangeProfession[0] = this->ui->spinBoxProfessionStart->text().toInt();
    if (this->ui->spinBoxProfessionEnd->text() != "")
        stream->rangeProfession[1] = this->ui->spinBoxProfessionEnd->text().toInt();
    if (this->ui->spinBoxSportStart->text() != "")
        stream->rangeSports[0] = this->ui->spinBoxSportStart->text().toInt();
    if (this->ui->spinBoxSportEnd->text() != "")
        stream->rangeSports[1] = this->ui->spinBoxSportEnd->text().toInt();
    this->hide();
}
