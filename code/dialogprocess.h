#ifndef DIALOGPROCESS_H
#define DIALOGPROCESS_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class DialogProcess;
}

class DialogProcess : public QDialog
{
    Q_OBJECT

public:
    explicit DialogProcess(QString char_num_str, QString time_lapse_str, QWidget *parent = 0);
    ~DialogProcess();
    int getcharnum();
    int getsplitcount();
    double gettimelapse();
    QString getText();
    void splitcountVisibility(bool uslov);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_DialogProcess_rejected();

private:
    Ui::DialogProcess *ui;
    int char_num = 0;
    double time_lapse = 0;
    int splitcount = 1;
    QString text = "#Cancel#";
};

#endif // DIALOGPROCESS_H
