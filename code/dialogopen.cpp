#include "dialogopen.h"
#include "ui_dialogopen.h"
#include <QPushButton>

DialogOpen::DialogOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpen)
{
    ui->setupUi(this);
    ui->plainTextEdit->setFixedHeight(25);
    ui->buttonBox->button(QDialogButtonBox::Open)->setText("Open");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
    setFixedSize(452,152);
}

DialogOpen::~DialogOpen()
{
    delete ui;
}

string DialogOpen::getName(){
    return name;
}

FileInfo::SubtitleFormat DialogOpen::getFormat(){
    return format;
}

void DialogOpen::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Open) ){
        if(ui->comboBox->currentIndex()==0){
            format = FileInfo::SubtitleFormat::SRT;
            name = ui->plainTextEdit->toPlainText().toStdString().append(".srt");
        }
        else if(ui->comboBox->currentIndex()==1){
            format = FileInfo::SubtitleFormat::MicroDVD;
            name = ui->plainTextEdit->toPlainText().toStdString().append(".txt");
        }
        else if(ui->comboBox->currentIndex()==2){
            format = FileInfo::SubtitleFormat::MPSub;
            name = ui->plainTextEdit->toPlainText().toStdString().append(".sub");
        }
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        name = "#Cancel#";
        this->close();
    }
}

void DialogOpen::on_DialogOpen_rejected()
{
    name = "#Cancel#";
    this->close();
}
