#include "capteurtension.h"
#include "tcpserveur.h"
#include <QDebug>

CapteurTension::CapteurTension()
    : i2c(I2C1, 0x49)
    , nivTension(0)
{
    QI2cDevice::connect(&timer, &QTimer::timeout, this, &CapteurTension::afficherTension);
    timer.start(30000);   // 30 000 ms = 30 s
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

    return tensionRe;   // le qDebug a été déplacé dans afficherTension()
}

void CapteurTension::afficherTension()
{
    getValue();   // met à jour nivTension
    qDebug() << "Tension batterie:" << nivTension << "V";
}

void CapteurTension::tension()
{
    if (getValue() < 0)                 // erreur de lecture : on n'envoie rien
        return;

    QString datatension = QString::number(nivTension, 'f', 2);   // ex. "7.84"
    serverBatterie.sendDatas(datatension);   // envoi aux clients TCP
    emit newTension(nivTension);             // envoi aux autres classes locales
}