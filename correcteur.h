//Consigne : la valeur qu’on veut (ex. 100).
//Entrée : la valeur mesurée par le capteur (ex. 80).
//Sortie : la commande envoyée aux moteurs pour corriger.



#ifndef CORRECTEUR_H
#define CORRECTEUR_H

#include <QObject>

class Correcteur : public QObject
{
    Q_OBJECT
public:
    explicit Correcteur(double _consigne, QObject *parent = nullptr);
public slots:
    virtual double process(double entree) = 0;//pas de code ici, les classes filles doivent l’écrire
protected://Ce qui suit est accessible par la classe et ses filles seulement.
    double consigne ;//L’attribut : un nombre à virgule qui stocke la consigne.

};

#endif // CORRECTEUR_H
//double est un type qui permet de stocker un nombre à virgule, comme la consigne ou le coefficient Kp.
//double process(double entree) : le premier double est ce que la méthode renvoie et celui entre parenthèses est ce qu’elle reçoit (la mesure).