#ifndef CAPTEURTENSION_H
#define CAPTEURTENSION_H

#include "qi2cdevice.h"
//#include "tcpserver.h"

#include <QDebug>
#include <QString>

class CapteurTension
{
public:
    CapteurTension();
    float getValue();
    void tension();

    // TcpServer Batterie;

private:
    QI2cDevice i2c;
    float nivTension;
    //unsigned char I2CAdresse = 0x49;
};

#endif // CAPTEURTENSION_H