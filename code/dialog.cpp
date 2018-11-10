#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setFixedSize(240,131);
}

Dialog::~Dialog()
{
    delete ui;
}

bool Dialog::getIspravi(){
    return ispravi;
}

QString Dialog::getText(){
    return text;
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        text = "Ok";
        ispravi = true;
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        text = "#Cancel#";
        ispravi = false;
        this->close();
    }
}

void Dialog::on_Dialog_rejected()
{
    this->close();
}
