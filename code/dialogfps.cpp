#include "dialogfps.h"
#include "ui_dialogfps.h"

DialogFPS::DialogFPS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFPS)
{
    ui->setupUi(this);
}

DialogFPS::~DialogFPS()
{
    delete ui;
}

double DialogFPS::getFPS(){
    return fps;
}

void DialogFPS::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        fps = ui->doubleSpinBox->value();
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        this->close();
    }
}

void DialogFPS::on_DialogFPS_rejected()
{
    this->close();
}
