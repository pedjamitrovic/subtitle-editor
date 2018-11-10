#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog>
#include <QPushButton>
#include "FileInfo.h"

namespace Ui {
class DialogSave;
}

class DialogSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSave(QWidget *parent = 0);
    ~DialogSave();
    string getName();
    FileInfo::SubtitleFormat getFormat();

private slots:

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_DialogSave_rejected();

private:
    Ui::DialogSave *ui;
    string name;
    FileInfo::SubtitleFormat format;
};

#endif // DIALOGSAVE_H
