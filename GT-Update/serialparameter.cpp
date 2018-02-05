#include "serialparameter.h"

SerialParameter::SerialParameter()
{
    portNum = "COM1";
    baudRate = "9600";
    parity = "无";
    dataBits = "8";
    stopBits = "1";
    flowControl = "无";
    appendType = 0;
    isHexShow = Qt::Unchecked;
    deviceType = 0;
}
