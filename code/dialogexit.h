#ifndef DIALOGEXIT_H
#define DIALOGEXIT_H

#include <QDialog>
#include <QPushButton>
#include "dialogsave.h"

namespace Ui {
class DialogExit;
}

class DialogExit : public QDialog
{
    Q_OBJECT

public:
    explicit DialogExit(QWidget *parent = 0);
    ~DialogExit();


private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogExit *ui;
    int errors = 0;
};

#endif // DIALOGEXIT_H
