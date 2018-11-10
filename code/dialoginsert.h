#ifndef DIALOGINSERT_H
#define DIALOGINSERT_H

#include <QDialog>
#include "TimeStamp.h"
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class dialoginsert;
}

class dialoginsert : public QDialog
{
    Q_OBJECT

public:
    explicit dialoginsert(QWidget *parent = 0);
    ~dialoginsert();
    TimeStamp* getPoc();
    TimeStamp* getKraj();
    QString getText();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_dialoginsert_rejected();

private:
    Ui::dialoginsert *ui;
    TimeStamp *poc, *kraj;
    QString text = "#Cancel#";
};

#endif // DIALOGINSERT_H
