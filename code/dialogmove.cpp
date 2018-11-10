#include "dialogmove.h"
#include "ui_dialogmove.h"

DialogMove::DialogMove(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMove)
{
    ui->setupUi(this);
    setFixedSize(325,129);
}

DialogMove::~DialogMove()
{
    delete ui;
}

TimeStamp* DialogMove::getPoc(){
    return poc;
}

TimeStamp* DialogMove::getKraj(){
    return kraj;
}

QString DialogMove::getText(){
    return text;
}

int DialogMove::getIndex(){
    return index;
}

void DialogMove::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        text = "Ok";
        QTime novpocetak(QTime::fromString(ui->starttimeEdit->text(),"hh:mm:ss.zzz"));
        QTime novkraj(QTime::fromString(ui->endtimeEdit->text(),"hh:mm:ss.zzz"));
        poc = new TimeStamp(novpocetak.hour(), novpocetak.minute(), novpocetak.second(), novpocetak.msec());
        kraj = new TimeStamp(novkraj.hour(), novkraj.minute(), novkraj.second(), novkraj.msec());
        interval = ui->doubleSpinBox->value();
        index = ui->comboBox->currentIndex();
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        text = "#Cancel#";
        this->close();
    }
}

void DialogMove::on_DialogMove_rejected()
{
    this->close();
}


double DialogMove::getInterval(){
    return interval;
}

void DialogMove::begendVisibility(bool uslov){
    if(uslov==true){
        ui->starttimeEdit->setVisible(true);
        ui->endtimeEdit->setVisible(true);
        ui->text_2->setVisible(true);
        ui->text_3->setVisible(true);
    }
    else{
        ui->starttimeEdit->setVisible(false);
        ui->endtimeEdit->setVisible(false);
        ui->text_2->setVisible(false);
        ui->text_3->setVisible(false);
    }
}

void DialogMove::comboVisibility(bool uslov){
    if(uslov==true) {
        ui->comboBox->setVisible(true);
        ui->doubleSpinBox->setMinimum(0);
    }
    else {
        ui->comboBox->setVisible(false);
        ui->doubleSpinBox->setMinimum(-3600);
    }
}
