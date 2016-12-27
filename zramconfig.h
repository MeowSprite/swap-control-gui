#ifndef ZRAMCONFIG_H
#define ZRAMCONFIG_H
#include <QString>
#include <QDir>
#include <QVector>

namespace Zram {

    class Config
    {
    public:
        Config(QMap<QString, QString>* config);
        bool saveToSystem();
        bool reload();

        bool enable;
        int size;
        int stream;
        QString type_alg;

        int ramSize;
        int cpuCount;

        QMap<QString, QString>* originConfig;
    };

    static QVector<QString> AlgTypes = {"lzo", "lz4", "deflate", "lz4hc"};
}

#endif // ZRAM_H
