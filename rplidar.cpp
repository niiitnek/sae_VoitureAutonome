#include "rplidar.h"
#include <QtMath>
#include <QDebug>

#ifndef _countof
#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))
#endif

RpLidar::RpLidar(const QString &portName, int baudRate, QObject *parent)
    : QObject(parent), drv(nullptr), _channel(nullptr), portName(portName), baudRate(baudRate)
{
    distances.fill(0, 360);
    scanTimer = new QTimer(this);
    connect(scanTimer, &QTimer::timeout, this, &RpLidar::readData);
}

RpLidar::~RpLidar()
{
    stopScan();
    if (drv) {
        drv->stop();
        drv->setMotorSpeed(0);
        delete drv;
        drv = nullptr;
    }
}

bool RpLidar::initialize()
{
    drv = *sl::createLidarDriver();
    if (!drv) {
        qDebug() << "Erreur : Impossible de créer le driver LIDAR";
        return false;
    }

    _channel = (*sl::createSerialPortChannel(portName.toLocal8Bit().constData(), baudRate));
    if (!_channel) {
        qDebug() << "Erreur : Impossible de créer le canal série";
        delete drv;
        drv = nullptr;
        return false;
    }

    sl_result op_result;
    sl_lidar_response_device_info_t devinfo;
    bool connectSuccess = false;

    if (SL_IS_OK(drv->connect(_channel))) {
        op_result = drv->getDeviceInfo(devinfo);
        if (SL_IS_OK(op_result)) {
            connectSuccess = true;
            qDebug() << "Connecté sur le lidar";
        } else {
            delete drv;
            drv = nullptr;
            return false;
        }
        qDebug() << "SLAMTEC LIDAR S/N:" << devinfo.serialnum;
        qDebug() << "Firmware Ver:" << (devinfo.firmware_version >> 8) << "." << (devinfo.firmware_version & 0xFF)
                 << "Hardware Rev:" << (int)devinfo.hardware_version;
    } else {
        qDebug() << "Erreur : Connexion au LIDAR échouée";
        delete drv;
        drv = nullptr;
        return false;
    }

    return connectSuccess;
}

void RpLidar::startScan()
{
    if (!drv) return;
    drv->setMotorSpeed();
    drv->startScan(0, 1);
    scanTimer->start(50); // Lecture toutes les 50ms
}

void RpLidar::stopScan()
{
    if (scanTimer->isActive()) {
        scanTimer->stop();
    }
    if (drv) {
        drv->stop();
        drv->setMotorSpeed(0);
    }
}

void RpLidar::readData()
{
    if (!drv) return;

    sl_lidar_response_measurement_node_hq_t nodes[8192];
    size_t count = _countof(nodes);
    sl_result op_result = drv->grabScanDataHq(nodes, count);

    if (SL_IS_OK(op_result)) {
        distances.fill(0);
        for (int i = 0; i < (int)count; i++) {
            int angle = qRound((nodes[i].angle_z_q14 * 90.f) / 16384.f);
            if (angle >= 180) angle = angle - 360;
            if ((angle >= -180) && (angle < 180)) {
                int d = nodes[i].dist_mm_q2 / 4.0;
                if (d > 0) distances.replace(angle + 180, d);
            }
        }

        // Interpolation des valeurs nulles
        for (int i = 0; i < 360; i++) {
            if (distances.at(i) == 0) {
                for (int j = 1; j < 10; j++) {
                    int pos = (i + j) % 360;
                    if (distances.at(pos) != 0) {
                        distances.replace(i, distances.at(pos));
                        break;
                    }
                }
            }
        }

        emit scanDataReady(distances);
    }
}