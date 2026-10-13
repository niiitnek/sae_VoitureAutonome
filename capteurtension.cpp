#include "capteurtension.h"

CapteurTension::CapteurTension()
    : i2c(I2C1, 0x49)
    , nivTension(0)
//, serverBatterie(????)
{
}

float CapteurTension::getValue()
{
    unsigned char data[2];

    if (!i2c.readRegisters(0x49, data, 2)) {
        qDebug() << "Erreur lecture MCP3021";
        return -1;
    }

    int valMesuree = ((data[0] << 8) | data[1]) >> 2;
    double tensionRe = (valMesuree / 1023.0) * 3.3;
    nivTension = tensionRe * ((10000.0 + 18000.0) / 10000.0);

    qDebug() << "Tension batterie:" << nivTension << "V";
    return tensionRe;
}

void CapteurTension::tension()
{
    double tension = getValue();
    QString datatension = QString::number(nivTension);
    //Batterie.tension(datatension);
}