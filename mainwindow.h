#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "zswapconfig.h"
#include "zramconfig.h"
#include "fileswapconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool loadCurrentConfig();

    ~MainWindow();

private slots:
    //for zswap tab
    void on_zwap_enable_stateChanged(int arg1);

    void on_pool_percent_slide_valueChanged(int value);

    void on_pool_percent_edit_textChanged(const QString &arg1);

    void on_zswap_save_clicked(bool checked);

    void on_zpool_type_currentIndexChanged(const QString &arg1);

    void on_compressor_type_currentIndexChanged(const QString &arg1);

    //for zram tab
    void on_ZramEnable_stateChanged(int arg1);

    void on_ZramSize_textEdited(const QString &arg1);

    void on_ZramStream_textEdited(const QString &arg1);

    void on_ZramAlgTypeCombox_currentIndexChanged(const QString &arg1);

    void on_ZramSaveBtn_clicked();

    //for fileswaptab

    void on_FcSwapEnable_stateChanged(int arg1);

    void on_FuSwapSize_textEdited(const QString &arg1);

    void on_FuSwapSizeSlide_sliderMoved(int position);

    void on_FcChunkSizeEdit_textEdited(const QString &arg1);

    void on_FcMaxCountEdit_textEdited(const QString &arg1);

    void on_FcPercentEdit_textEdited(const QString &arg1);

    void on_FileSwapSaveBtn_clicked();

    void on_StartServiceBtn_clicked();

    void on_ServiceEnable_clicked();

private:
    Ui::MainWindow *ui;
    Zswap::Config* zswap;
    Zram::Config* zram;
    FileSwap::Config* fileswap;

    bool serviceEnable;

    void updateWidgetState();

    //for zwap
    bool loadCurrentZSwapConfig();
    void updateZswapTabState();
    void initZswapTabPage();
    void setupZswapTabPage();

    //for zram
    bool loadCurrentZRamConfig();
    void initZramTabPage();
    void setupZramTabPage();
    void updateZramTabState();

    //for fileswap
    bool loadCurrentFileSwapConfig();
    void initFileSwapTabPage();
    void setupFileSwapTabPage();
    void updateFileSwapTabState();


};

#endif // MAINWINDOW_H
