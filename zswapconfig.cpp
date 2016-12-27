#include "zswapconfig.h"
#include <common.h>
#include <QDebug>
#include <QTextStream>

namespace Zswap {
    Config::Config(QMap<QString, QString> *config)
    {
        originConfig = config;
        reload();
    }

    bool Config::saveToSystem()
    {
        QMap<QString, QString> change;
        change["zswap_enabled"] = enable?"1":"0";
        change["zswap_compressor"] = type_compressor;
        change["zswap_max_pool_percent"] = QString::number(max_pool_percent);
        change["zswap_zpool"] = type_zpool;
        qDebug() << "Zswap Config Save" << change << endl;
        Common::setConfigValue(Common::ConfigFilePath, change);
    }

    bool Config::reload()
    {
        enable = Common::isTrue((*originConfig)["zswap_enabled"]);
        max_pool_percent = (*originConfig)["zswap_max_pool_percent"].toInt();
        type_zpool = (*originConfig)["zswap_zpool"];
        type_compressor = (*originConfig)["zswap_compressor"];
        qDebug() << "loaded zswap config" << enable << max_pool_percent << type_zpool << type_compressor << endl;
        return true;
    }
}

