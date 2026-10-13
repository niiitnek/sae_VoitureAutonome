#include "materielsimule.h"
#include <qdebug.h>
MaterielSimule::MaterielSimule()
    : Materiel{}
{
    tcp.connectTCP("10.98.33.29");// Connexion au simulateur
    connect(&tcp, &TcpClient::newDatas, this, &MaterielSimule::processTcpDatas);
    // Chaque message reçu par tcp est envoyé à processTcpDatas
}
void MaterielSimule::deplacer(double vitesse, double angle)
{
    // Fabrique le message "vitesse;angle", par exemple "0.5;0"
    QString message = QString::number(vitesse) + ";" + QString::number(angle);
    tcp.sendDatas(message); // l'envoie au simulateur
    emit newState(vitesse, angle);// annonce le nouvel état
}
void MaterielSimule::processTcpDatas(QString data)
{
     // Découpe "120;130;..." en une liste de textes
    QStringList liste = data.split(';');
    if (liste.size() == 360)// Trame valide = exactement 360 valeurs
    {
        for (int i = 0; i < 360; i++)
            distanceLidar[i] = liste[i].toInt();// case i = angle convertit le texte "120" en entier 120.
    }
    qDebug()<<liste;
    emit newDistances();// prévient que le tableau est à jour
}