#ifndef RPLIDAR_H
#define RPLIDAR_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include "sl_lidar_driver.h"

class RpLidar : public QObject
{
    Q_OBJECT
public:
    explicit RpLidar(const QString &portName = "/dev/ttyUSB0", int baudRate = 115200, QObject *parent = nullptr);
    ~RpLidar();

    bool initialize();
    void startScan();
    void stopScan();

signals:
    void scanDataReady(const QVector<int> &distances);

private slots:
    void readData();

private:
    sl::ILidarDriver *drv;
    sl::IChannel *_channel;
    QString portName;
    int baudRate;
    QTimer *scanTimer;
    QVector<int> distances;
};

#endif // RPLIDAR_H