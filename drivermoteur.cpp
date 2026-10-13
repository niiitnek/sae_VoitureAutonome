#include "drivermoteur.h"

DriverMoteur::DriverMoteur()
    :i2c(I2C1, 0x58)//initialisation de la communication i2c en utillisant le bus i2c (I2C1) avec une adresse i2c (0x58)
{
    setaccel(100);
}

void DriverMoteur::setVitesse(double vitesse)
{


    // gestion de la direction
    if (vitesse < 0) {
        i2c.writeRegister(0,1);
        vitesse = -vitesse; // on change le signe car  on a gere la direction juste au dessus
    }
    else i2c.writeRegister(0,2);


    // gestion de la vitesse

    if (vitesse > 1) vitesse = 1;
    i2c.writeRegister(2,vitesse*250);

}


void DriverMoteur::setaccel(int accel)
{
    if (accel > 0 and accel < 255) i2c.writeRegister(3,accel);
    else i2c.writeRegister(3,255);
}
