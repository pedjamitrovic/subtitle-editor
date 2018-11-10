#include "dialoginsert.h"
#include "ui_dialoginsert.h"

dialoginsert::dialoginsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialoginsert)
{
    ui->setupUi(this);
    setFixedSize(452,152);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Insert");
}

dialoginsert::~dialoginsert()
{
    delete ui;
}

TimeStamp* dialoginsert::getPoc(){
    return poc;
}

TimeStamp* dialoginsert::getKraj(){
    return kraj;
}

QString dialoginsert::getText(){
    return text;
}

void dialoginsert::on_buttonBox_clicked(QAbstractButton *button)
{
    if(button == ui->buttonBox->button(QDialogButtonBox::Ok) ){
        QTime novpocetak(QTime::fromString(ui->starttimeEdit->text(),"hh:mm:ss.zzz"));
        QTime novkraj(QTime::fromString(ui->endtimeEdit->text(),"hh:mm:ss.zzz"));
        text = ui->textEdit->toPlainText();
        poc = new TimeStamp(novpocetak.hour(), novpocetak.minute(), novpocetak.second(), novpocetak.msec());
        kraj = new TimeStamp(novkraj.hour(), novkraj.minute(), novkraj.second(), novkraj.msec());
        this->close();
    }
    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel) ){
        text = "#Cancel#";
        this->close();
    }
}

void dialoginsert::on_dialoginsert_rejected()
{
    this->close();
}


