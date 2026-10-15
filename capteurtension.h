#ifndef CAPTEURTENSION_H
#define CAPTEURTENSION_H

#include "qi2cdevice.h"
#include "tcpserveur.h"
//#include "tcpserver.h"

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTimer>

class CapteurTension : public QObject
{
    Q_OBJECT
public:
    CapteurTension();
    float getValue();
    void tension();

private slots:
    void afficherTension();   // affiche la tension toutes les 30 s

private:
    QI2cDevice i2c;
    QTimer timer;
    float nivTension;
    TcpServeur serverBatterie{2008};
    //unsigned char I2CAdresse = 0x49;

signals:
    void newTension(double tension);
};

#endif // CAPTEURTENSION_H
