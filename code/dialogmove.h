#ifndef DIALOGMOVE_H
#define DIALOGMOVE_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include "TimeStamp.h"

namespace Ui {
class DialogMove;
}

class DialogMove : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMove(QWidget *parent = 0);
    ~DialogMove();
    TimeStamp* getPoc();
    TimeStamp* getKraj();
    QString getText();
    int getIndex();
    double getInterval();
    void begendVisibility(bool uslov);
    void comboVisibility(bool uslov);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_DialogMove_rejected();

private:
    Ui::DialogMove *ui;
    TimeStamp *poc, *kraj;
    QString text = "#Cancel#";
    double interval;
    int index;
};

#endif // DIALOGMOVE_H
