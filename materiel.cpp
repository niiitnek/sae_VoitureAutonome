#include "materiel.h"

Materiel::Materiel()
{
}
array<int, 360> &Materiel::getDistancesLidar()
{
    return distanceLidar; // renvoie le tableau lui-même, pas une copie
}


