#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "dialogopen.h"
#include "dialoggreske.h"
#include "dialogexit.h"
#include "dialogsave.h"
#include "dialoginsert.h"
#include "dialogfps.h"
#include "dialogprocess.h"
#include "dialogmove.h"
#include "SubtitleProcessing.h"
#include "SRT.h"
#include "MPSub.h"
#include "MicroDVD.h"
#include "TimeStamp.h"
#include "SubtitleApp.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusBar()->setSizeGripEnabled(false);
    processor = nullptr;
    app = nullptr;
    setFixedSize(800,500);
    ui->table->setColumnWidth(0,30);
    ui->table->setColumnWidth(1,80);
    ui->table->setColumnWidth(2,80);
    ui->table->setColumnWidth(3,60);
    ui->table->horizontalHeader()->setStretchLastSection(true);
    ui->table->verticalHeader()->hide();
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    QString info = "Open subtitle to start editing.";
    refreshcurrentInfo(info);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete processor;
}

void MainWindow::setApp(SubtitleApp* application){
    app = application;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    if (app->getIO()!=nullptr){
        event->ignore();
        DialogExit dg;
        dg.setModal(true);
        dg.exec();
    }
}

void MainWindow::refreshTable(){
        ui->table->setRowCount((int)processor->getTitles()->numberOfSubtitles());
        int i=0;
        for (map<long long int, Subtitle*>::const_iterator it = processor->getTitles()->getMap().cbegin(); it != processor->getTitles()->getMap().cend(); ++it, i++) {
            QTime pocetak((*it).second->dohPocetak()->geth(),(*it).second->dohPocetak()->getm() ,(*it).second->dohPocetak()->gets() , (*it).second->dohPocetak()->getms());
            QTime kraj((*it).second->dohKraj()->geth(),(*it).second->dohKraj()->getm() ,(*it).second->dohKraj()->gets() , (*it).second->dohKraj()->getms());
            ui->table->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->table->setItem(i,1,new QTableWidgetItem(pocetak.toString("hh:mm:ss.zzz")));
            ui->table->setItem(i,2,new QTableWidgetItem(kraj.toString("hh:mm:ss.zzz")));
            ui->table->setItem(i,3,new QTableWidgetItem(QString::number((*it).second->dohTrajanje(),'f',3)));
            ui->table->setItem(i,4,new QTableWidgetItem(QString::fromStdString((*it).second->dohTekst())));
            ui->table->item(i,0)->setTextAlignment(Qt::AlignCenter);
            ui->table->item(i,1)->setTextAlignment(Qt::AlignCenter);
            ui->table->item(i,2)->setTextAlignment(Qt::AlignCenter);
            ui->table->item(i,3)->setTextAlignment(Qt::AlignCenter);
        }
        checkTimes();
        if (processor->getTitles()->numberOfSubtitles()>0) ui->table->setCurrentCell(0,0);
}

void MainWindow::refreshcurrentInfo(QString info){
    ui->currentInfo->setText(info);
}

void MainWindow::refreshInfo(){
   QString info = "";
   info.append("Opened file info:\n\nTitles duration - ");
   QTime duration(app->getIO()->getFileInfo()->gettitlesduration()->geth(),app->getIO()->getFileInfo()->gettitlesduration()->getm(),app->getIO()->getFileInfo()->gettitlesduration()->gets(),app->getIO()->getFileInfo()->gettitlesduration()->getms());
   info.append(duration.toString("hh:mm:ss.zzz"));
   info.append("\nFormat - ");
   if(app->getIO()->getFileInfo()->getformat()==FileInfo::SubtitleFormat::SRT){
       info.append("SubRip");
   }
   else if (app->getIO()->getFileInfo()->getformat()==FileInfo::SubtitleFormat::MicroDVD){
       info.append("MicroDVD");
   }
   else if (app->getIO()->getFileInfo()->getformat()==FileInfo::SubtitleFormat::MPSub){
       info.append("MPlayer");
   }
   info.append("\nNumber of titles - ");
   info.append(QString::number(app->getIO()->getFileInfo()->gettitlecount()));
   info.append("\nFile size in bytes - ");
   info.append(QString::number((int)app->getIO()->getFileInfo()->getfilesize()));
   ui->textBrowser->setText(info);
}

long long int MainWindow::getKey(QTime time){
    TimeStamp vreme(time.hour(),time.minute(),time.second(),time.msec());
    return vreme.hashKey();
}

void MainWindow::on_table_cellClicked(int row)
{
    if(app->getIO() == nullptr) return;
    if(processor->getTitles()->numberOfSubtitles()>0){
        ui->textEdit->setPlainText(ui->table->item(row, 4)->text());
        ui->starttimeEdit->setTime(QTime::fromString(ui->table->item(row,1)->text()));
        ui->endtimeEdit->setTime(QTime::fromString(ui->table->item(row,2)->text()));
        QString temp;
        temp.append("Selected ranges: (");
        temp.append(QString::number(ui->table->selectedRanges().first().topRow()+1));
        temp.append("-");
        temp.append(QString::number(ui->table->selectedRanges().first().bottomRow()+1));
        temp.append(")");
        ui->ranges->setText(temp);
    }
    ui->ranges->setVisible(true);
    ui->rowLabel->setVisible(true);
}

void MainWindow::on_textEdit_textChanged()
{
    if(app->getIO()==nullptr) return;
    if (processor->getTitles()->numberOfSubtitles()>0) {
        ui->table->item(ui->table->currentRow(), 4)->setText(ui->textEdit->toPlainText());
        QTime vreme(QTime::fromString(ui->table->item(ui->table->currentRow(),1)->text(),"hh:mm:ss.zzz"));
        processor->setText(getKey(vreme), ui->textEdit->toPlainText().toStdString().c_str());
    }
}

void MainWindow::on_table_currentCellChanged(int currentRow)
{
    if(app->getIO()==nullptr) return;
    if(processor->getTitles()->numberOfSubtitles()>0){
        ui->textEdit->setPlainText(ui->table->item(currentRow, 4)->text());
        ui->starttimeEdit->setTime(QTime::fromString(ui->table->item(currentRow,1)->text()));
        ui->endtimeEdit->setTime(QTime::fromString(ui->table->item(currentRow,2)->text()));
        QString temp;
        temp.append("Selected ranges: (");
        temp.append(QString::number(ui->table->selectedRanges().first().topRow()+1));
        temp.append("-");
        temp.append(QString::number(ui->table->selectedRanges().first().bottomRow()+1));
        temp.append(")");
        ui->ranges->setText(temp);
        temp="";
        temp.append(QString::number(currentRow+1));
        temp.append("/");
        temp.append(QString::number(ui->table->rowCount()));
        ui->rowLabel->setText(temp);
    }
    ui->ranges->setVisible(true);
    ui->rowLabel->setVisible(true);
}

void MainWindow::on_actionOpen_triggered()
{
    DialogOpen dialog;
    dialog.setModal(true);
    dialog.exec();
    if(dialog.getName()!="#Cancel#"){
        try{
            DialogFPS d;
            QString fileName(dialog.getName().c_str());
            if(!QFileInfo::exists(fileName)) throw GreskaOtvaranje();
            if(dialog.getFormat()==FileInfo::SubtitleFormat::SRT){
                app->setNewIO(new SRT(dialog.getName().c_str()));
            }
            else if (dialog.getFormat()==FileInfo::SubtitleFormat::MicroDVD){
                d.setModal(true);
                d.exec();
                app->setNewIO(new MicroDVD(dialog.getName().c_str(),d.getFPS()));
            }
            else if (dialog.getFormat()==FileInfo::SubtitleFormat::MPSub){
                app->setNewIO(new MPSub(dialog.getName().c_str()));
            }
            app->setNewTitles(app->getIO()->getTitles());
            if (processor!=nullptr) delete processor;
            processor = new SubtitleProcessing(app->getIO()->getTitles());
            refreshTable();
            refreshInfo();
            QString info = "You have successfully opened file. Current FPS = ";
            if (dialog.getFormat()==FileInfo::SubtitleFormat::MicroDVD) info.append(QString::number(d.getFPS()));
            else info.append(QString::number(25));
            info.append(".");
            refreshcurrentInfo(info);
        }
        catch(GreskaOtvaranje g){
            DialogGreske dg;
            dg.setModal(true);
            dg.setLabelName("File could not be opened. Check if it exists.");
            dg.exec();
        }
        catch(GreskaFormat g){
            DialogGreske dg;
            dg.setModal(true);
            dg.setLabelName("Subtitle format error.\nSupported formats are: SubRip, MicroDVD, MPlayer");
            dg.exec();
        }
        catch(GreskaFPS g){
            DialogGreske dg;
            dg.setModal(true);
            dg.setLabelName("Invalid FPS value.");
            dg.exec();
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    if(app->getIO()!=nullptr){
        DialogExit dg;
        dg.setModal(true);
        dg.exec();
    }
    else QCoreApplication::exit();
}

void MainWindow::on_actionSave_triggered()
{
    if (app->getIO()!=nullptr){
            if(errors!=0){
                Dialog d;
                d.setModal(true);
                d.exec();
                if(d.getText()!="#Cancel#"){
                    on_resolveButton_clicked();
                }
                else return;
            }
            DialogSave ds;
            ds.setModal(true);
            ds.exec();
            SubtitleIO* siowrite;
            if(ds.getName()!="#Cancel#"){
                if(ds.getFormat()==FileInfo::SubtitleFormat::SRT){
                    siowrite = new SRT();
                }
                else if (ds.getFormat()==FileInfo::SubtitleFormat::MicroDVD){
                    siowrite = new MicroDVD();
                }
                else if (ds.getFormat()==FileInfo::SubtitleFormat::MPSub){
                    siowrite = new MPSub();
                }
                siowrite->setTitles(app->getIO()->getTitles());
                siowrite->writeFile(ds.getName().c_str());
                siowrite->setTitles(nullptr);
                delete siowrite;
                QString info = "You have successfully saved file.";
                refreshcurrentInfo(info);
        }
    }
    else{
        DialogGreske dg;
        dg.setModal(true);
        dg.setLabelName("You need to open subtitle before you save it.");
        dg.exec();
    }
}

void MainWindow::on_deleteItems_clicked()
{
   if(ui->table->rowCount()>0){
       int i = ui->table->selectedRanges().first().topRow();
       int j = ui->table->selectedRanges().first().bottomRow();
       int z = j-i;
       while(i <= j){
            QTime vreme(QTime::fromString(ui->table->item(j,1)->text(),"hh:mm:ss.zzz"));
            processor->deleteOneTitle(getKey(vreme));
            ui->table->removeRow(j);
            j--;
        }
        for(int k=0; k<processor->getTitles()->numberOfSubtitles(); k++){
            ui->table->setItem(k,0,new QTableWidgetItem(QString::number(k+1)));
            ui->table->item(k,0)->setTextAlignment(Qt::AlignCenter);
        }
        QString info = "You have successfully deleted ";
        info.append(QString::number(z+1));
        info.append(" title(s).");
        refreshTable();
        refreshcurrentInfo(info);
        if(processor->getTitles()->numberOfSubtitles()==0) {
            ui->ranges->setVisible(false);
            ui->rowLabel->setVisible(false);
        }
    }
}

void MainWindow::on_changeTime_clicked()
{
         try{
         if(ui->table->rowCount()>0){
             QTime novpocetak(QTime::fromString(ui->starttimeEdit->text(),"hh:mm:ss.zzz"));
             QTime novkraj(QTime::fromString(ui->endtimeEdit->text(),"hh:mm:ss.zzz"));
             QTime pocetak(QTime::fromString(ui->table->item(ui->table->currentRow(),1)->text(),"hh:mm:ss.zzz"));
             string text = ui->textEdit->toPlainText().toStdString().c_str();
             TimeStamp* poc = new TimeStamp(novpocetak.hour(), novpocetak.minute(), novpocetak.second(), novpocetak.msec());
             TimeStamp* kraj = new TimeStamp(novkraj.hour(), novkraj.minute(), novkraj.second(), novkraj.msec());

             if(novpocetak!=pocetak){
                 if(! processor->addOneTitle(getKey(novpocetak), new Subtitle(poc, kraj, text)) ) throw GreskaVreme();
                 processor->deleteOneTitle(getKey(pocetak));
             }
             else {
                 processor->setEndTime(getKey(pocetak), kraj);
                 ui->table->setItem(ui->table->currentRow(),2,new QTableWidgetItem(novkraj.toString("hh:mm:ss.zzz")));
                 delete poc;
             }
             refreshTable();
             QString info = "You have successfully changed time at row ";
             info.append(QString::number(ui->table->currentRow()+1));
             info.append(".");
             refreshcurrentInfo(info);
         }
    }
    catch(GreskaVreme gv){
        DialogGreske dg;
        dg.setModal(true);
        dg.setLabelName("Subtitle at input start time already exists.");
        dg.exec();
    }
}

void MainWindow::checkTimes(){
    int i = 0, j = 0;
    for (map<long long int, Subtitle*>::const_iterator it = processor->getTitles()->getMap().cbegin(); it != processor->getTitles()->getMap().cend(); ++it, i++) {
       if ((*it).second->dohTrajanje()<0){
           ui->table->item(i, 3)->setBackgroundColor(QColor::fromRgb(255,40,40));
           j++;
       }
    }
    i = 1;
    for (map<long long int, Subtitle*>::const_iterator it1 = processor->getTitles()->getMap().cbegin(); i < processor->getTitles()->getMap().size() ; ++it1, ++i) {
        map<long long int, Subtitle*>::const_iterator it2 = it1;
        ++it2;
        if(*(it1->second->dohKraj()) > *(it2->second->dohPocetak())){
            ui->table->item(i-1, 2)->setBackgroundColor(QColor::fromRgb(255,110,110));
            ui->table->item(i, 1)->setBackgroundColor(QColor::fromRgb(255,110,110));
            j++;
        }
    }

    QString text("Titles have ");
    text.append(QString::number(j));
    text.append(" error(s).");
    errors = j;
    ui->timeErrors->setText(text);
}

void MainWindow::on_insertItem_clicked()
{
    if(app->getIO()!=nullptr){
        QString info;
        dialoginsert di;
        di.setModal(true);
        di.exec();
        if(di.getText()!="#Cancel#"){
            Subtitle* novi = new Subtitle(di.getPoc(), di.getKraj(), di.getText().toStdString().c_str());
            if(processor->addOneTitle(di.getPoc()->hashKey(), novi)) {
                info = "You have successfully inserted title. ";
                refreshcurrentInfo(info);
                refreshTable();
            }
            else {
                DialogGreske dg;
                dg.setModal(true);
                dg.setLabelName("Subtitle at input start time already exists.");
                dg.exec();
            }
       }
    }
}

void MainWindow::on_actionInsert_row_triggered()
{
    on_insertItem_clicked();
}

void MainWindow::on_actionDelete_row_s_triggered()
{
    on_deleteItems_clicked();
}

void MainWindow::on_actionChange_FPS_triggered()
{
    if(app->getIO()!=nullptr){
        DialogFPS d;
        d.setModal(true);
        d.exec();
        app->getIO()->setFPS(d.getFPS());
        QString info = "You have successfully changed FPS. Current FPS = ";
        info.append(QString::number(d.getFPS()));
        info.append(".");
        refreshcurrentInfo(info);
    }
}

void MainWindow::on_mergeButton_clicked()
{
    if(app->getIO()!=nullptr){
        DialogProcess dp(QString("Maximum char number: "), QString("Maximum time lapse: "));
        dp.splitcountVisibility(false);
        dp.setModal(true);
        dp.exec();
        if(dp.getText()!="#Cancel#"){
            if(ui->applyToAll->isChecked()){
                int counter = processor->mergeEveryTwo(dp.gettimelapse(), (size_t)dp.getcharnum());
                QString info = "Successfully merged ";
                info.append(QString::number(counter));
                info.append(" titles.");
                refreshcurrentInfo(info);
            }
            else{
                int i = ui->table->selectedRanges().first().topRow();
                int j = ui->table->selectedRanges().first().bottomRow();
                if ((j-i)!=1){
                    DialogGreske dg;
                    dg.setModal(true);
                    dg.setLabelName("You have selected invalid range.\nCheck \"Apply to all\" if you want to try to merge \nall successive titles.");
                    dg.exec();
                    return;
                }
                else{
                    QTime prvi(QTime::fromString(ui->table->item(i,1)->text(),"hh:mm:ss.zzz"));
                    QTime drugi(QTime::fromString(ui->table->item(j,1)->text(),"hh:mm:ss.zzz"));
                    if(processor->mergeTwo(processor->getExactTitle(getKey(prvi)), processor->getExactTitle(getKey(drugi)), dp.gettimelapse(), (size_t)dp.getcharnum())){
                        QString info = "Successfully merged titles ";
                        info.append(QString::number(i+1));
                        info.append(" and ");
                        info.append(QString::number(j+1));
                        info.append(".");
                        refreshcurrentInfo(info);
                    }
                    else{
                        QString info = "Merging titles ";
                        info.append(QString::number(i+1));
                        info.append(" and ");
                        info.append(QString::number(j+1));
                        info.append(" was unsuccessfull.");
                        refreshcurrentInfo(info);
                    }
                }
            }
            refreshTable();
            if (processor->getTitles()->numberOfSubtitles()>0) ui->table->setCurrentCell(0,1);
        }
    }
}

void MainWindow::on_actionMerge_two_triggered()
{
    on_mergeButton_clicked();
}

void MainWindow::on_splitButton_clicked()
{
    if(app->getIO()!=nullptr){
        DialogProcess dp(QString("Minimum char number: "), QString("Minimum duration: "));
        dp.splitcountVisibility(true);
        dp.setModal(true);
        dp.exec();
        if(dp.getText()!="#Cancel#"){
            if(ui->applyToAll->isChecked()){
                int counter = processor->splitEveryToMore(dp.gettimelapse(), (size_t)dp.getcharnum(), (size_t)dp.getsplitcount());
                QString info = "Successfully split ";
                info.append(QString::number(counter));
                info.append(" titles.");
                refreshcurrentInfo(info);
            }
            else{
                int i = ui->table->currentRow();
                QTime pocetak(QTime::fromString(ui->table->item(i,1)->text(),"hh:mm:ss.zzz"));
                    if(processor->splitToMore(processor->getExactTitle(getKey(pocetak)), dp.gettimelapse(), (size_t)dp.getcharnum(), (size_t)dp.getsplitcount())){
                        QString info = "Successfully split title ";
                        info.append(QString::number(i+1));
                        info.append(".");
                        refreshcurrentInfo(info);
                    }
                    else{
                        QString info = "Spliting title ";
                        info.append(QString::number(i));
                        info.append(" was unsuccessfull.");
                        refreshcurrentInfo(info);
                    }
            }
            refreshTable();
            if (processor->getTitles()->numberOfSubtitles()>0) ui->table->setCurrentCell(0,1);
        }
    }
}

void MainWindow::on_actionSplit_to_more_triggered()
{
    on_splitButton_clicked();
}

void MainWindow::on_moveButton_clicked()
{
    if(app->getIO()!=nullptr){
        DialogMove di;
        di.setModal(true);
        di.comboVisibility(false);
        if(ui->applyToAll->isChecked()) di.begendVisibility(false);
        else di.begendVisibility(true);
        di.exec();
        if(di.getText()!="#Cancel#"){
            if(ui->applyToAll->isChecked()){
                int counter = processor->moveAllTimes(di.getInterval());
                QString info = "Successfully moved ";
                info.append(QString::number(counter));
                info.append(" titles.");
                refreshcurrentInfo(info);
            }
            else{
                    int counter = processor->moveSpecificTimes(di.getPoc()->vreme(), di.getKraj()->vreme(), di.getInterval());
                    QString info = "Successfully moved ";
                    info.append(QString::number(counter));
                    info.append(" titles.");
                    refreshcurrentInfo(info);
           }
        refreshTable();
        if (processor->getTitles()->numberOfSubtitles()>0) ui->table->setCurrentCell(0,1);
        }
    }
}

void MainWindow::on_actionMove_in_time_triggered()
{
    on_moveButton_clicked();
}

void MainWindow::on_distanceButton_clicked()
{
    if(app->getIO()!=nullptr){
        DialogMove di;
        di.setModal(true);
        di.comboVisibility(true);
        if(ui->applyToAll->isChecked()) di.begendVisibility(false);
        else di.begendVisibility(true);
        di.exec();
        if(di.getText()!="#Cancel#"){
            if(ui->applyToAll->isChecked()){
                if(di.getIndex()==0){
                    int counter = processor->increaseAllDistance(di.getInterval());
                    QString info = "Successfully increased distance of ";
                    info.append(QString::number(counter));
                    info.append(" titles.");
                    refreshcurrentInfo(info);
                }
                else{
                    int counter = processor->decreaseAllDistance(di.getInterval());
                    QString info = "Successfully decreased distance of ";
                    info.append(QString::number(counter));
                    info.append(" titles.");
                    refreshcurrentInfo(info);
                }
            }
            else{
                if(di.getIndex()==0){
                    processor->increaseSpecificDistance(di.getPoc()->vreme(), di.getKraj()->vreme(), di.getInterval());
                    QString info = "Successfully increased distance of titles.";
                    refreshcurrentInfo(info);
                }
                else{
                    processor->decreaseSpecificDistance(di.getPoc()->vreme(), di.getKraj()->vreme(), di.getInterval());
                    QString info = "Successfully decreased distance of titles.";
                    refreshcurrentInfo(info);
                }
           }
        refreshTable();
        if (processor->getTitles()->numberOfSubtitles()>0) ui->table->setCurrentCell(0,1);
        }
    }
}

void MainWindow::on_actionChange_distance_triggered()
{
    on_distanceButton_clicked();
}


void MainWindow::on_resolveButton_clicked()
{
    if(app->getIO()!=nullptr){
        processor->resolveErrors();
        QString info = "Successfully resolved all errors.";
        refreshcurrentInfo(info);
        refreshTable();
    }
}

void MainWindow::on_actionResolve_errors_triggered()
{
    on_resolveButton_clicked();
}
