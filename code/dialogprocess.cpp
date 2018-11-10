#include "dialogprocess.h"
#include "ui_dialogprocess.h"

DialogProcess::DialogProcess(QString char_num_str, QString time_lapse_str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogProcess)
{
    ui->setupUi(this);
    ui->labelint->setText(char_num_str);
    ui->labeldouble->setText(time_lapse_str);
}

DialogProcess::~DialogProcess()
{
    delete ui;
}

int DialogProcess::getcharnum(){
    return char_num;
}

double DialogProcess::gettimelapse(){
    return time_lapse;
}

QString DialogProcess::getText(){
    return text;
}

int DialogProcess::getsplitcount(){
    return splitcount;
}

void DialogProcess::splitcountVisibility(bool uslov){
    if(uslov==true){
        ui->splitcountlabel->setText("Split count: ");
        ui->splitcountlabel->setVisible(true);
        ui->splitspinBox->setVisible(true);
    }
    else{
        ui->splitcountlabel->setVisible(false);
        ui->splitspinBox->setVisible(false);
    }
}

void DialogProcess::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        char_num = ui->spinBox->value();
        time_lapse = ui->doubleSpinBox->value();
        splitcount = ui->splitspinBox->value();
        text = "Ok";
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        this->close();
    }
}

void DialogProcess::on_DialogProcess_rejected()
{
    this->close();
}

