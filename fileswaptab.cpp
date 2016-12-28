#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QMessageBox>
#include <common.h>


bool MainWindow::loadCurrentFileSwapConfig()
{
    this->fileswap->reload();
    return true;
}

void MainWindow::initFileSwapTabPage()
{
    ui->FuSwapSize->setValidator(new QIntValidator(0, zram->ramSize, this));
    ui->FuSwapSizeSlide->setMaximum(zram->ramSize);
    ui->FcChunkSizeEdit->setValidator(new QIntValidator(0, zram->ramSize, this));
    ui->FcPercentEdit->setValidator(new QIntValidator(0, 99, this));
}

void MainWindow::setupFileSwapTabPage()
{

    if(fileswap->fuEnabled)
        ui->FuSwapSize->setText(QString::number(fileswap->fuSize));
    else
        ui->FuSwapSize->setText(QString::number(0));

    ui->FcSwapEnable->setChecked(fileswap->fcEnabled);
    ui->FcChunkSizeEdit->setText(QString::number(fileswap->fcChunkSize));
    ui->FcMaxCountEdit->setText(QString::number(fileswap->fcMaxCount));
    ui->FcPercentEdit->setText(QString::number(fileswap->fcPercent));
}

void MainWindow::updateFileSwapTabState()
{
    ui->FcChunkSizeEdit->setEnabled(fileswap->fcEnabled);
    ui->FcMaxCountEdit->setEnabled(fileswap->fcEnabled);
    ui->FcPercentEdit->setEnabled(fileswap->fcEnabled);
}

void MainWindow::on_FuSwapSize_textEdited(const QString &arg1)
{
    qDebug() << "fuswap size edit" << arg1 << endl;
    fileswap->fuSize = arg1.toInt();
    fileswap->fuEnabled = fileswap->fuSize != 0;
    ui->FuSwapSizeSlide->setValue(fileswap->fuSize);
}

void MainWindow::on_FuSwapSizeSlide_sliderMoved(int position)
{
    fileswap->fuSize = position;
    fileswap->fuEnabled = fileswap->fuSize != 0;
    ui->FuSwapSize->setText(QString::number(fileswap->fuSize));
}

void MainWindow::on_FcSwapEnable_stateChanged(int arg1)
{
    if(arg1 != 0) {
        fileswap->fcEnabled = true;
    }
    else {
        fileswap->fcEnabled = false;
    }
    this->updateWidgetState();
}


void MainWindow::on_FcChunkSizeEdit_textEdited(const QString &arg1)
{
    fileswap->fcChunkSize = arg1.toInt();
}

void MainWindow::on_FcMaxCountEdit_textEdited(const QString &arg1)
{
    fileswap->fcMaxCount = arg1.toInt();
}

void MainWindow::on_FcPercentEdit_textEdited(const QString &arg1)
{
    fileswap->fcPercent = arg1.toInt();
}

void MainWindow::on_FileSwapSaveBtn_clicked()
{
    if(fileswap->saveToSystem()){
        QMessageBox msg;
        msg.setWindowTitle("修改结果");
        msg.setText("保存成功");
        msg.exec();
    }
}


