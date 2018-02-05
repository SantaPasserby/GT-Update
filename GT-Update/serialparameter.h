#ifndef SERIALPARAMETER_H
#define SERIALPARAMETER_H
#include <QString>
#include <QCheckBox>

class SerialParameter
{
public:
    SerialParameter();

    QString portNum;
    QString baudRate;
    QString parity;
    QString dataBits;
    QString stopBits;
    QString flowControl;
    qint8 appendType;
    Qt::CheckState isHexShow;
    qint8   deviceType;

};

#endif // SERIALPARAMETER_H
