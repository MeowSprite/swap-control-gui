#include "zramconfig.h"
#include "common.h"

namespace Zram {

Config::Config(QMap<QString, QString> *config)
{
    originConfig = config;
    reload();
}

bool Config::saveToSystem()
{
    QMap<QString, QString> change;
    change["zram_enabled"] = enable?"1":"0";
    change["zram_size"] = QString::number(size*1024) + 'K';
    change["zram_streams"] = QString::number(stream);
    change["zram_alg"] = type_alg;
    qDebug() << "Zram Config Save" << change << endl;
    Common::setConfigValue(Common::ConfigFilePath, change);
}

bool Config::reload()
{
    ramSize = (*originConfig)["ram_size"].toInt()/1024;
    cpuCount = (*originConfig)["cpu_count"].toInt();

    enable = Common::isTrue((*originConfig)["zram_enabled"]);
    size = Common::getNumberFromUnit((*originConfig)["zram_size"])/1024;
    stream = (*originConfig)["zram_streams"].toInt();
    type_alg = (*originConfig)["zram_alg"];
    qDebug() << "loaded zram config" << enable << size << stream << type_alg << endl;
    return true;
}

}


