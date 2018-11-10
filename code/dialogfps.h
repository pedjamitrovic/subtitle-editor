#ifndef DIALOGFPS_H
#define DIALOGFPS_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>


namespace Ui {
class DialogFPS;
}

class DialogFPS : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFPS(QWidget *parent = 0);
    ~DialogFPS();
    double getFPS();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_DialogFPS_rejected();

private:
    Ui::DialogFPS *ui;
    double fps = 25;
};

#endif // DIALOGFPS_H
