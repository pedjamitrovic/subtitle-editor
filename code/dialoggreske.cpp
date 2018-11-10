#include "dialoggreske.h"
#include "ui_dialoggreske.h"

DialogGreske::DialogGreske(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogGreske)
{
    ui->setupUi(this);
    setFixedSize(277,121);
}

DialogGreske::~DialogGreske()
{
    delete ui;
}

void DialogGreske::on_pushButton_clicked()
{

}

void DialogGreske::setLabelName(QString str){
    ui->label->setText(str);
}
