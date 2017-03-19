#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    qDebug() << QLocale::system().name() << endl;
    if (translator.load("translations/" + QLocale::system().name())) {
        a.installTranslator(&translator);
        qDebug() << QLocale::system().name() << endl;
    }
    MainWindow w;
    w.show();

    return a.exec();
}
