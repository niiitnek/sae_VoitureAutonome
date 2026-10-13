#ifndef SUIVREBORD_H
#define SUIVREBORD_H

#include "comportement.h"
#include "correcteur.h"
class SuivreBord : public Comportement
{
    Q_OBJECT
public:
    explicit SuivreBord(std::array<int, 360> &distancelidar, Correcteur &correcteur, int _vitesse, int _angleReference, QObject *parent = nullptr);
public slots:
    void process() override;
protected:
    Correcteur &c;
    int index = 0;
    int angle = 0;
    int vitesse = 0 ;
};

#endif // SUIVREBORD_H




