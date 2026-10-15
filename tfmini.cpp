
#include "tfmini.h"
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

TfMini::TfMini(I2C_BUS bus, unsigned char adComposant,
                 QObject *parent)
    : QI2cDevice(bus, adComposant, parent),
    adresse(adComposant)
{
    const char *devname = nullptr;

    switch (bus) {
    case I2C0: devname = "/dev/i2c-0"; break;
    case I2C1: devname = "/dev/i2c-1"; break;
    case I2C2: devname = "/dev/i2c-2"; break;
    default:
        throw std::runtime_error("Bus I2C invalide");
    }

    lidarFile = ::open(devname, O_RDWR);

    if (lidarFile < 0)
        throw std::runtime_error("Impossible d'ouvrir le bus I2C");

    if (ioctl(lidarFile, I2C_SLAVE, adresse) < 0) {
        ::close(lidarFile);
        lidarFile = -1;
        throw std::runtime_error("Impossible de configurer le TFmini-I2C");
    }
}

TfMini::~TfMini()
{
    if (lidarFile >= 0)
        ::close(lidarFile);
}

void TfMini::lireValeur()
{
    unsigned char commande[3] = {0x01, 0x02, 0x07};
    unsigned char data[7] = {};

    i2c_msg messages[2] = {};

    // L'adresse est celle définie dans le constructeur.
    messages[0].addr = adresse;
    messages[0].flags = 0;
    messages[0].len = sizeof(commande);
    messages[0].buf = commande;

    messages[1].addr = adresse;
    messages[1].flags = I2C_M_RD;
    messages[1].len = sizeof(data);
    messages[1].buf = data;

    i2c_rdwr_ioctl_data transfert = {};
    transfert.msgs = messages;
    transfert.nmsgs = 2;

    if (::ioctl(lidarFile, I2C_RDWR, &transfert) < 0) {
        perror("Erreur lecture TFmini-I2C");
        return;
    }

    unsigned int distance =
        static_cast<unsigned int>(data[1]) |
        (static_cast<unsigned int>(data[2]) << 8);

    unsigned int force =
        static_cast<unsigned int>(data[3]) |
        (static_cast<unsigned int>(data[4]) << 8);

    if (distance == 0xFFFF || force < 20) {
        qDebug() << "Mesure invalide";
        return;
    }

    qDebug() << "Distance du lidar" << adresse
             << ":" << distance << "cm";
}