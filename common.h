#ifndef COMMON_H
#define COMMON_H

#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QIODevice>
#include <QProcess>
#include <QRegExp>

namespace Common {
    static QString ConfigFilePath = "/home/meows/project/shell-tool/systemd-swap/swap_test.conf";
    static QString ScriptPath = "/home/meows/project/qtproject/swap-control/shell/";
    static QString ServiceName = "systemd-swap";

    static QString getContent(const QString& path){
        QFile f(path);
        f.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream fileStream(&f);
        QString content;
        fileStream>>content;
        return content;
    }

    //when some string is like "23454kb"
    static int64_t getNumberFromUnit(const QString& str) {
        QRegExp rx("^([0-9]*).*");
        int pos = str.indexOf(rx);
        if(pos >= 0) {
            QString a = rx.capturedTexts().at(1);
            return a.toLong();
        }
    }

    static bool isTrue(const QString& str){
        if(str == "Yes" || str == "Y" || str== "1" || str == "true") {
            return true;
        }
        return false;
    }

    static int setConfigValue(const QString& path, const QMap<QString, QString>& changeList) {
        auto tmpdir = QDir::temp();
        QFile cmdFile(tmpdir.absoluteFilePath("swapcontrol-cmd-list"));
        if(!cmdFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            return 1;
        }
        QTextStream fileIn(&cmdFile);
        fileIn << "#!/bin/bash\n";
        for(auto& c : changeList.toStdMap()) {
            QString cmd;
            QTextStream in(&cmd);
            in << "sed -i 's,^\\(" << c.first << "=\\).*,\\1'"<< c.second << "',' " << path <<"\n";
            fileIn << cmd;
        }
        cmdFile.close();    //we must close or flush file stream
        QProcess exec;
        QStringList arguments;
        arguments << "/bin/sh " + QFileInfo(cmdFile).absoluteFilePath();
        exec.start("gksudo", arguments);
        exec.waitForFinished();
        QByteArray out = exec.readAll();
        int returnCode = exec.exitCode();
        return returnCode;
    }

    static QMap<QString, QString>* loadConfig(const QString& path) {
        static QMap<QString, QString> originConfig;
        QProcess exec;
        QStringList arguments;
        exec.setProcessChannelMode(QProcess::MergedChannels);
        arguments   << ScriptPath + "listvalue.sh"
                    << path;
        exec.start("/bin/bash", arguments);
        exec.waitForFinished();
        QByteArray out = exec.readAllStandardOutput();
        int returnCode = exec.exitCode();
        QStringList groups = QString(out).split("\n");
        for (int i = 0; i < groups.size() - 1; ++i) {   //the last element is empty
            QStringList pair = groups.at(i).split('=');
            originConfig[pair.at(0)] = pair.at(1);
        }
        if(returnCode != 0) {
            return nullptr;
        }
        return &originConfig;
    }

    static bool restartService() {
        QProcess exec;
        QStringList arguments;
        exec.setProcessChannelMode(QProcess::MergedChannels);
        arguments << "restart" << ServiceName;
        exec.start("systemctl", arguments);
        exec.waitForFinished();
        return true;
    }

    static bool enableService(bool enable) {
        QProcess exec;
        QStringList arguments;
        exec.setProcessChannelMode(QProcess::MergedChannels);
        arguments << (enable?"enable":"disable") << ServiceName;
        exec.start("systemctl", arguments);
        exec.waitForFinished();
        int code = exec.exitCode();
        qDebug() << code << endl;
        return code==0;
    }

    static bool isServiceEnable() {
        QProcess exec;
        QStringList arguments;
        exec.setProcessChannelMode(QProcess::MergedChannels);
        arguments << "is-enabled" << ServiceName;
        exec.start("systemctl", arguments);
        exec.waitForFinished();
        int code = exec.exitCode();
        return code == 0;
    }
}

#endif // COMMON_H
