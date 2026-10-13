#include "servo.h"

#include <QFile>
#include <QByteArray>
#include <QThread>
#include <QDebug>

Servo::Servo(float _offset_ms,float _amplitude_ms)
    :offset_ms(_offset_ms),amplitude_ms(_amplitude_ms)
{

}

void Servo::initialisation()
{
    // Exporter PWM2 si le canal n'est pas déjà exporté
    if (!QFile::exists("/sys/class/pwm/pwmchip0/pwm2"))
    {
        QFile exportPWM("/sys/class/pwm/pwmchip0/export");

        if (!exportPWM.open(QIODevice::WriteOnly))
        {
            qDebug() << "Erreur export :" << exportPWM.errorString();
            return;
        }

        exportPWM.write(QByteArray::number(2));
        exportPWM.flush();
        exportPWM.close();

        QThread::msleep(10);
    }
    // Mettre duty_cycle à zéro avant de modifier period
    QFile duty("/sys/class/pwm/pwmchip0/pwm2/duty_cycle");

    if (!duty.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Erreur duty_cycle :" << duty.errorString();
        return;
    }

    duty.write(QByteArray::number(0));
    duty.flush();
    duty.close();

    // Configurer la période à 20 ms
    QFile periode("/sys/class/pwm/pwmchip0/pwm2/period");

    if (!periode.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Erreur period :" << periode.errorString();
        return;
    }

    periode.write(QByteArray::number(20000000));
    periode.flush();
    periode.close();

    // Activer la PWM
    QFile enable("/sys/class/pwm/pwmchip0/pwm2/enable");

    if (!enable.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Erreur enable :" << enable.errorString();
        return;
    }

    enable.write(QByteArray::number(1));
    enable.flush();
    enable.close();

    qDebug() << "PWM initialisée";
}
void Servo::position(double angle)
{
    // Limiter l'angle normalisé entre -1 et 1
    if (angle < -1.0)
        angle = -1.0;

    if (angle > 1.0)
        angle = 1.0;

    // Convertir la valeur normalisée en impulsion PWM
    // -1 : 1 ms
    //  0 : 1,5 ms
    // +1 : 2 ms
    int impulsion_ns = offset_ms*1000000 + (amplitude_ms*1000000 * angle);
    qDebug() << (amplitude_ms*1000000);
    QFile duty("/sys/class/pwm/pwmchip0/pwm2/duty_cycle");

    if (!duty.open(QIODevice::WriteOnly))
    {
        qDebug() << "Erreur ouverture duty_cycle :"
                 << duty.errorString();
        return;
    }

    duty.write(QByteArray::number(impulsion_ns));
    duty.flush();
    duty.close();

    qDebug() << "Angle normalisé :" << angle
             << "Impulsion (ns) :" << impulsion_ns;
}
