#ifndef WIDGETLIDAR_H
#define WIDGETLIDAR_H

#include <QWidget>
#include <array>

class WidgetLidar : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetLidar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void processTcpDatas(QString data);

private:
    std::array<int, 360> distancesLidar;   // une distance par degré
};

#endif