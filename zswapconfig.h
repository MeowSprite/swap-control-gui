#ifndef ZSWAPCONFIG_H
#define ZSWAPCONFIG_H
#include <QString>
#include <QDir>
#include <QVector>

namespace Zswap {
    class Config
    {
    public:
        Config(QMap<QString, QString>* config);
        bool saveToSystem();
        bool reload();

        bool support;
        bool enable;
        int max_pool_percent;
        QString type_zpool;
        QString type_compressor;

        QMap<QString, QString>* originConfig;
    };

    static QDir ZSwapDir("/sys/module/zswap");
    static QDir ZSwapParameterDir("/sys/module/zswap/parameters");
    static QVector<QString> ZpoolTypes = {"zbud", "zsmalloc"};
    static QVector<QString> CompressorTypes = {"lzo", "lz4"};
}


#endif // ZSWAPCONFIG_H
