#ifndef WIDGETVOITURE_H
#define WIDGETVOITURE_H

#include <QWidget>

class WidgetVoiture : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetVoiture(QWidget *parent = nullptr);
    double vitesse;
    double angle;
public slots:
    void processTcpDatas(QString datas);
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // WIDGETVOITURE_H
