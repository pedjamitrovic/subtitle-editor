#ifndef DIALOGOPEN_H
#define DIALOGOPEN_H
#include "SRT.h"
#include "MPSub.h"
#include "MicroDVD.h"

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class DialogOpen;
}

class DialogOpen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOpen(QWidget *parent = 0);
    ~DialogOpen();
    string getName();
    FileInfo::SubtitleFormat getFormat();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_DialogOpen_rejected();

private:
    Ui::DialogOpen *ui;
    string name;
    FileInfo::SubtitleFormat format;
};

#endif // DIALOGOPEN_H
