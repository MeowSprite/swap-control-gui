#ifndef FILESWAPCONFIG_H
#define FILESWAPCONFIG_H
#include <QString>
#include <QDir>
#include <QVector>

namespace FileSwap {

class Config
{
public:
    Config(QMap<QString, QString>* config);
    bool saveToSystem();
    bool reload();

    // swapfu
    bool fuEnabled;
    int fuSize;

    //swapfc
    bool fcEnabled;
    int fcChunkSize;
    int fcMaxCount;
    int fcPercent;



    QMap<QString, QString>* originConfig;
};

}

#endif // FILESWAPCONFIG_H
