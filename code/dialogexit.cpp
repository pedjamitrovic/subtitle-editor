#include "dialogexit.h"
#include "ui_dialogexit.h"
#include "dialog.h"

DialogExit::DialogExit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogExit)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Save)->setText("Save First");
    setFixedSize(244,108);
}

DialogExit::~DialogExit()
{
    delete ui;
}

void DialogExit::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Yes) ){
       QCoreApplication::exit();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Save) ){
        DialogSave ds;
        ds.setModal(true);
        ds.exec();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        this->close();
    }
}
