#ifndef CORRECTEURPROPORTIONNEL_H
#define CORRECTEURPROPORTIONNEL_H

#include "correcteur.h"

class CorrecteurProportionnel : public Correcteur
{
    Q_OBJECT
public:

    explicit CorrecteurProportionnel(double _consigne, double _kp, QObject *parent = nullptr);
public slots:
    double process(double entree);//On reprend la méthode de la mère
private: //n’est accessible que dans cette classe
      double kp;//L’attribut propre à la fille
};

#endif // CORRECTEURPROPORTIONNEL_H