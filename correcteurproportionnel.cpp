#include "correcteurproportionnel.h"

CorrecteurProportionnel::CorrecteurProportionnel(double _consigne, double _kp, QObject *parent)
    : Correcteur(_consigne, parent),
    kp(_kp)
{
}

double CorrecteurProportionnel::process(double entree)//La méthode reçoit la mesure du capteur (un double) et renvoie la sortie (un double).
{
    double erreur = consigne - entree; // On calcule l’écart entre ce qu’on veut et ce qu’on mesure.
    double sortie = kp * erreur;       //Kp c est la correction
    return sortie;//On renvoie le résultat
}