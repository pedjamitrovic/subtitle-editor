#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTime>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include <QFileInfo>

class SubtitleApp;
class SubtitleProcessing;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setApp(SubtitleApp* application);
    void closeEvent (QCloseEvent *event);
    void refreshTable();
    void refreshcurrentInfo(QString info);
    void refreshInfo();
    void checkTimes();
    void refreshRanges();
    long long int getKey(QTime time);

private slots:
    void on_table_cellClicked(int row);

    void on_textEdit_textChanged();

    void on_table_currentCellChanged(int currentRow);

    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_deleteItems_clicked();

    void on_changeTime_clicked();

    void on_insertItem_clicked();

    void on_actionInsert_row_triggered();

    void on_actionDelete_row_s_triggered();

    void on_actionChange_FPS_triggered();

    void on_mergeButton_clicked();

    void on_actionMerge_two_triggered();

    void on_splitButton_clicked();

    void on_actionSplit_to_more_triggered();

    void on_moveButton_clicked();

    void on_actionMove_in_time_triggered();

    void on_distanceButton_clicked();

    void on_actionChange_distance_triggered();

    void on_resolveButton_clicked();

    void on_actionResolve_errors_triggered();

private:
    Ui::MainWindow *ui;
    SubtitleApp* app;
    SubtitleProcessing* processor;
    int errors = 0;
};

#endif // MAINWINDOW_H
