#ifndef DRIVERMOTEUR_H
#define DRIVERMOTEUR_H

#include "qi2cdevice.h"

class DriverMoteur
{
public:
    DriverMoteur();
    void setVitesse(double vitesse);
    void setaccel(int accel);
private:
    QI2cDevice i2c;

};

#endif // DRIVERMOTEUR_H
