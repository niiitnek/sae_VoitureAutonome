#include "suivrebord.h"

SuivreBord::SuivreBord(std::array<int, 360> &distancelidar, Correcteur &correcteur, int _vitesse, int _angleReference, QObject *parent)
    : Comportement(distancelidar, parent), c(correcteur), vitesse(_vitesse)
{
    index = (_angleReference % 360 + 360) % 360;
}



void SuivreBord::process()
{

    int distanceMesuree = distancesLidar[index];

    double correction  = c.process(distanceMesuree);
    emit deplacer(vitesse,correction);
}
