#include "fileswapconfig.h"
#include "common.h"

namespace FileSwap {

Config::Config(QMap<QString, QString> *config)
{
    originConfig = config;
    reload();
}

bool Config::saveToSystem()
{
    QMap<QString, QString> change;
    change["swapfu_enabled"] = fuEnabled?"1":"0";
    change["swapfu_size"] = QString::number(fuSize*1024) + 'K';
    change["swapfc_enabled"] = fcEnabled?"1":"0";
    change["swapfc_chunk_size"] = QString::number(fcChunkSize) + 'M';
    change["swapfc_max_count"] = QString::number(fcMaxCount);
    change["swapfc_free_swap_perc"] = QString::number(fcPercent);
    qDebug() << "FileSwap Config Save" << change << endl;
    Common::setConfigValue(Common::ConfigFilePath, change);
}

bool Config::reload()
{
    fuEnabled = Common::isTrue((*originConfig)["swapfu_enabled"]);
    fuSize = Common::getNumberFromUnit((*originConfig)["swapfu_size"])/1024;

    fcEnabled = Common::isTrue((*originConfig)["swapfc_enabled"]);
    fcChunkSize = Common::getNumberFromUnit((*originConfig)["swapfc_chunk_size"]);
    fcMaxCount = (*originConfig)["swapfc_max_count"].toInt();
    fcPercent = (*originConfig)["swapfc_free_swap_perc"].toInt();
    qDebug() << "loaded swapfile config" << fuEnabled
             << fuSize << fcEnabled << fcChunkSize
             << fcMaxCount << fcPercent << endl;
}

}
