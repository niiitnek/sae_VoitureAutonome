#include "correcteur.h"

Correcteur::Correcteur(double _consigne, QObject *parent)
    : QObject(parent),
    consigne(_consigne)
{
}