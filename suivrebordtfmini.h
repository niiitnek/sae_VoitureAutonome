#ifndef SUIVREBORDTFMINI_H
#define SUIVREBORDTFMINI_H

#include "comportement.h"
#include "correcteur.h"

// Suivi de bord adapté au TFmini (un seul capteur sur le côté).
// Lit la distance dans distancesLidar[angle], remplie par MaterielReel.
//
//  correction = P + D
//   P : ton Correcteur (ex : CorrecteurProportionnel) -> kp * (consigne - distance)
//   D : kd * (distance précédente - distance)          -> freine quand on fonce vers
//       le mur ou qu'on s'en éloigne vite : c'est ce qui empêche les zigzags
//
//  + médiane sur 3 mesures (supprime les mesures aberrantes sans retard)
//  + braquage limité et progressif (pas de coup de volant)
class SuivreBordTfMini : public Comportement
{
    Q_OBJECT
public:
    explicit SuivreBordTfMini(std::array<int, 360> &distancelidar,
                              Correcteur &correcteur,
                              float _vitesse,          // vitesse en ligne droite
                              int _angleTfMini = 90,   // case du tableau du TFmini
                              double _kd = 40.0,       // amortissement (anti-zigzag)
                              int _distanceArretMm = 300,  // obstacle devant plus près -> arrêt
                              int _angleAvant = 0,         // case du tableau du TFmini de devant
                              QObject *parent = nullptr);

public slots:
    void process() override;

protected:
    int filtrerMediane(int distanceMesuree);

    Correcteur &c;
    float vitesse;
    int index;
    double kd;
    int distanceArretMm;
    int indexAvant;

    // Médiane sur 3 mesures
    int mesures[3] = {0, 0, 0};
    int nbMesures = 0;
    int position = 0;

    int distancePrecedente = -1;     // -1 = pas encore de mesure
    double correctionActuelle = 0.0;

    const double zoneMorte      = 15.0;   // petite correction ignorée
    const double correctionMax  = 432.0;  // 432 / 720 = 0,6 : braquage max
    const double variationMax   = 72.0;   // 72 / 720 = 0,1 : le volant tourne d'au plus 0,1 par cycle
};

#endif // SUIVREBORDTFMINI_H
