#ifndef DIALOGGRESKE_H
#define DIALOGGRESKE_H

#include <QDialog>

namespace Ui {
class DialogGreske;
}

class DialogGreske : public QDialog
{
    Q_OBJECT

public:
    explicit DialogGreske(QWidget *parent = 0);
    ~DialogGreske();
    void setLabelName(QString str);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DialogGreske *ui;
};

#endif // DIALOGGRESKE_H
