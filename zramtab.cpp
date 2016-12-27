#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QMessageBox>
#include <common.h>


bool MainWindow::loadCurrentZRamConfig()
{
    this->zram->reload();
    return true;
}


void MainWindow::initZramTabPage()
{
    for(auto type : Zram::AlgTypes) {
        ui->ZramAlgTypeCombox->addItem(type, type);
    }
    ui->ZramSize->setValidator( new QIntValidator(0, zram->ramSize, this) );
    ui->ZramStream->setValidator( new QIntValidator(0, zram->cpuCount * 2, this) );
}

void MainWindow::setupZramTabPage()
{
    ui->ZramEnable->setChecked(zram->enable);
    ui->ZramSize->setText(QString::number(zram->size));
    ui->ZramStream->setText(QString::number(zram->stream));
    int index;
    index = ui->ZramAlgTypeCombox->findData(zram->type_alg);
    if(index != -1) {
        ui->ZramAlgTypeCombox->setCurrentIndex(index);
    } else {
        qDebug() << "Zram cannot match the alg type" << zram->type_alg << endl;
    }
}

void MainWindow::updateZramTabState()
{
    ui->ZramSize->setEnabled(zram->enable);
    ui->ZramStream->setEnabled(zram->enable);
    ui->ZramAlgTypeCombox->setEnabled(zram->enable);
}

//signal

void MainWindow::on_ZramEnable_stateChanged(int arg1)
{
    if(arg1 != 0) {
        zram->enable = true;
    }
    else {
        zram->enable = false;
    }
    this->updateWidgetState();
}


void MainWindow::on_ZramSize_textEdited(const QString &arg1)
{
    zram->size = arg1.toInt();
}

void MainWindow::on_ZramStream_textEdited(const QString &arg1)
{
    zram->stream = arg1.toInt();
}

void MainWindow::on_ZramAlgTypeCombox_currentIndexChanged(const QString &arg1)
{
    zram->type_alg = arg1;
}

void MainWindow::on_ZramSaveBtn_clicked()
{
    if(zram->saveToSystem() == 0){
        QMessageBox msg;
        msg.setWindowTitle("修改结果");
        msg.setText("保存成功");
        msg.exec();
    }
}
