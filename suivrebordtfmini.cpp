#include "suivrebordtfmini.h"
#include <QtGlobal>
#include <algorithm>
#include <cmath>

SuivreBordTfMini::SuivreBordTfMini(std::array<int, 360> &distancelidar,
                                   Correcteur &correcteur,
                                   float _vitesse,
                                   int _angleTfMini,
                                   double _kd,
                                   int _distanceArretMm,
                                   int _angleAvant,
                                   QObject *parent)
    : Comportement(distancelidar, parent),
    c(correcteur),
    vitesse(_vitesse),
    kd(_kd),
    distanceArretMm(_distanceArretMm)
{
    index = (_angleTfMini % 360 + 360) % 360;
    indexAvant = (_angleAvant % 360 + 360) % 360;
}

int SuivreBordTfMini::filtrerMediane(int distanceMesuree)
{
    mesures[position] = distanceMesuree;
    position = (position + 1) % 3;
    if (nbMesures < 3)
    {
        nbMesures++;
        return distanceMesuree;      // pas encore 3 mesures
    }

    int tri[3] = {mesures[0], mesures[1], mesures[2]};
    std::sort(tri, tri + 3);
    return tri[1];                   // valeur du milieu
}

void SuivreBordTfMini::process()
{
    // 0) Obstacle devant (TFmini 0x16) trop proche : arrêt, roues droites
    int distanceAvant = distancesLidar[indexAvant];
    if (distanceAvant > 0 && distanceAvant < distanceArretMm)
    {
        correctionActuelle = 0;
        emit deplacer(0, 0);
        return;
    }

    int distanceMesuree = distancesLidar[index];

    // Pas de mesure : on avance tout droit
    if (distanceMesuree <= 0)
    {
        emit deplacer(vitesse, 0);
        return;
    }

    // 1) Filtre : supprime les mesures aberrantes
    int distance = filtrerMediane(distanceMesuree);

    // 2) P : ton correcteur -> kp * (consigne - distance)
    double correction = c.process(distance);

    // 3) D : on regarde si la voiture se rapproche ou s'éloigne du mur
    //    se rapproche -> correction positive (s'écarter) avant d'être trop près
    //    s'éloigne    -> correction négative (revenir) avant d'être trop loin
    if (distancePrecedente > 0)
        correction += kd * (distancePrecedente - distance);
    distancePrecedente = distance;

    // 4) Petite correction ignorée, braquage limité
    if (std::abs(correction) < zoneMorte)
        correction = 0;
    correction = qBound(-correctionMax, correction, correctionMax);

    // 5) Braquage progressif : pas de coup de volant
    double variation = qBound(-variationMax, correction - correctionActuelle, variationMax);
   correctionActuelle = correctionActuelle + variation;

    // 6) On ralentit un peu quand on braque
    double vitesseVirage = vitesse * (1.0 - 0.3 * std::abs(correctionActuelle) / correctionMax);



    emit deplacer(vitesseVirage, correctionActuelle);
}
