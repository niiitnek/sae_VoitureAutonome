#ifndef MATERIEL_H
#define MATERIEL_H

#include <QObject>
#include <array>
#include "tcpserveur.h"
using namespace std;
class Materiel : public QObject
{
    Q_OBJECT
public:
    explicit Materiel();
    array<int,360> & getDistancesLidar();
public slots:
    // En slot pour que le comportement puisse s'y connecter avec connect()
    virtual void deplacer(double vitesse, double angle)=0;
signals:
    //Prévenir les autres classes (la stratégie) que le tableau lidar est à jour.
    void newDistances();
    //Prévenir les autres classes (l’IHM) de la vitesse et de l’angle actuels.
    void newState(double vitesse, double angle);
protected :
    // 360 distances, une par degré (case i = distance à l'angle i)
    // protected : accessible seulement par Materiel et ses classes filles
    array<int, 360> distanceLidar;
private:
    TcpServeur tcpServeur; // serveur vers l'IHM (vide pour l'instant)
};

#endif // MATERIEL_H
