#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QStringList>
#include <QMessageBox>
#include <QCoreApplication>
#include <common.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Common::setPathAfterApplicationInit();
    serviceEnable = Common::isServiceEnable();
    //load global config
    auto config = Common::loadConfig(Common::ConfigFilePath);
    if(!config) {
        qDebug() << "error load config error" << endl;
        QCoreApplication::quit();
        //todo: deal with load config error
    }
    //init config instances
    this->zswap = new Zswap::Config(config);
    this->zram = new Zram::Config(config);
    this->fileswap = new FileSwap::Config(config);

    ui->setupUi(this);
    //init pages
    this->initZswapTabPage();
    this->initZramTabPage();
    this->initFileSwapTabPage();
    //load config && show config in widget
    this->loadCurrentConfig();
    this->updateWidgetState();
}

bool MainWindow::loadCurrentConfig(){
    this->loadCurrentZSwapConfig();
    this->setupZswapTabPage();
    this->loadCurrentZRamConfig();
    this->setupZramTabPage();
    this->loadCurrentFileSwapConfig();
    this->setupFileSwapTabPage();
    return true;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete zswap;
    delete zram;
}

void MainWindow::updateWidgetState()
{
    this->updateZswapTabState();
    this->updateZramTabState();
    this->updateFileSwapTabState();

    ui->ServiceEnable->setChecked(serviceEnable);
}

void MainWindow::on_StartServiceBtn_clicked()
{
    Common::restartService();
}

void MainWindow::on_ServiceEnable_clicked()
{
    serviceEnable = !serviceEnable;
    if(!Common::enableService(serviceEnable)){
        serviceEnable = !serviceEnable;
        ui->ServiceEnable->setChecked(serviceEnable);
    }
}
