#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QMessageBox>
#include <common.h>


bool MainWindow::loadCurrentZSwapConfig(){
    this->zswap->reload();
    return true;
}

void MainWindow::updateZswapTabState()
{
    ui->pool_percent_edit->setEnabled(zswap->enable);
    ui->pool_percent_slide->setEnabled(zswap->enable);
    ui->compressor_type->setEnabled(zswap->enable);
    ui->zpool_type->setEnabled(zswap->enable);
}

void MainWindow::initZswapTabPage()
{

    for(auto type : Zswap::CompressorTypes) {
        ui->compressor_type->addItem(type, type);
    }
    for(auto type : Zswap::ZpoolTypes) {
        ui->zpool_type->addItem(type, type);
    }
    ui->pool_percent_edit->setValidator( new QIntValidator(0, 100, this) );
}

void MainWindow::setupZswapTabPage()
{
    ui->zwap_enable->setChecked(this->zswap->enable);
    ui->pool_percent_slide->setValue(this->zswap->max_pool_percent);

    int index;
    index = ui->compressor_type->findData(zswap->type_compressor);
    if(index != -1) {
        ui->compressor_type->setCurrentIndex(index);
    } else {
        qDebug() << "cannot match the compressor type" << zswap->type_compressor << endl;
    }
    index = ui->zpool_type->findData(zswap->type_zpool);
    if(index != -1) {
        ui->zpool_type->setCurrentIndex(index);
    } else {
        qDebug() << "cannot match the zpool type" << zswap->type_zpool << endl;
    }
    ui->pool_percent_edit->setText(QString::number(zswap->max_pool_percent));
}

//ui signal
void MainWindow::on_pool_percent_slide_valueChanged(int value)
{
    ui->pool_percent_edit->setText(QString::number(value));
}

void MainWindow::on_pool_percent_edit_textChanged(const QString &arg1)
{
    int value = arg1.toInt(Q_NULLPTR, 0);
    ui->pool_percent_slide->setValue(value);
    zswap->max_pool_percent = value;
}

void MainWindow::on_zwap_enable_stateChanged(int arg1)
{
    if(arg1 != 0) {
        zswap->enable = true;
    }
    else {
        zswap->enable = false;
    }
    this->updateWidgetState();
}

void MainWindow::on_zpool_type_currentIndexChanged(const QString &arg1)
{
    zswap->type_zpool = arg1;
}

void MainWindow::on_compressor_type_currentIndexChanged(const QString &arg1)
{
    zswap->type_compressor = arg1;
}


void MainWindow::on_zswap_save_clicked(bool checked)
{
    if(zswap->saveToSystem() == 0){
        QMessageBox msg;
        msg.setWindowTitle("修改结果");
        msg.setText("保存成功");
        msg.exec();
    }
}
