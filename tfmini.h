#ifndef TFMINI_H
#define TFMINI_H
#include "qi2cdevice.h"

class TfMini : public QI2cDevice
{
public:
    TfMini(I2C_BUS bus, unsigned char adComposant,
           QObject *parent = nullptr);
    ~TfMini();

    void lireValeur();

private:
    const unsigned char adresse;
    int lidarFile = -1;
};

#endif // RPLIDAR_H