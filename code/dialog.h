#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    bool getIspravi();
    QString getText();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_Dialog_rejected();

private:
    Ui::Dialog *ui;
    bool ispravi = false;
    QString text = "#Cancel#";
};

#endif // DIALOG_H
