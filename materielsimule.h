#ifndef MATERIELSIMULE_H
#define MATERIELSIMULE_H
#include "materiel.h"
#include "tcpclient.h"
// Classe FILLE : matériel qui communique avec le simulateur
class MaterielSimule : public Materiel
{
public:
    explicit MaterielSimule();
    // override : remplit la fonction virtuelle pure de Materiel
    virtual void deplacer(double vitesse, double angle) override;
public slots:
    // Reçoit les messages du simulateur (trame lidar)
    void processTcpDatas(QString data);
private:
    TcpClient tcp;  //Gérer la communication réseau avec le simulateur.
};

#endif // MATERIELSIMULE_H
