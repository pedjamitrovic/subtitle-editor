#include "dialogsave.h"
#include "ui_dialogsave.h"

DialogSave::DialogSave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
    setFixedSize(447,155);
    ui->TextEdit->setFixedHeight(25);
    name = "#Cancel#";
}

DialogSave::~DialogSave()
{
    delete ui;
}

string DialogSave::getName(){
    return name;
}

FileInfo::SubtitleFormat DialogSave::getFormat(){
    return format;
}

void DialogSave::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Save) ){
        name = ui->TextEdit->toPlainText().toStdString();
        if(ui->comboBox->currentIndex()==0){
           format = FileInfo::SubtitleFormat::SRT;
        }
        else if(ui->comboBox->currentIndex()==1){
          format = FileInfo::SubtitleFormat::MicroDVD;
        }
        else if(ui->comboBox->currentIndex()==2){
          format = FileInfo::SubtitleFormat::MPSub;
        }
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel)){
        this->close();
    }
}

void DialogSave::on_DialogSave_rejected()
{
    this->close();
}
