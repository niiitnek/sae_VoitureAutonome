#include "widgetlidar.h"
#include <QPainter>
#include <QtMath>

WidgetLidar::WidgetLidar(QWidget *parent) : QWidget(parent)
{
    for (int i = 0; i < 360; i++)
        distancesLidar[i] = 0;             // aucune mesure au départ
}

void WidgetLidar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;

    int centreX = width() / 2;             // centre du widget = position de la voiture
    int centreY = height() / 2;

    // Fond blanc
    pen.setWidth(1);
    pen.setColor(QColor(0, 0, 0));
    painter.setBrush(QColor(255, 255, 255));
    painter.setPen(pen);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    // Traits du lidar
    pen.setWidth(1);
    pen.setColor(QColor(0, 0, 255)); //bleu
    painter.setPen(pen);

    for (int angle = 0; angle < 360; angle ++)
    {
        int mesure = distancesLidar[angle];
        if (mesure > 3000)
            mesure = 3000;                 // 3k max de dist

        double d = mesure / 4.0;           // zoom
        double rad = qDegreesToRadians((double)angle+180);    // degré en radians pour use cos et sin

        double x = centreX + d * cos(rad);                // point d'arrivée du trait
        double y = centreY - d * sin(rad);                // le - car y descend sur l'écran

        painter.drawLine(QPointF(centreX, centreY), QPointF(x, y));
    }

    // Voiture
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0));
    painter.setBrush(QColor(255, 0, 0));
    painter.setPen(pen);
    painter.drawRect(centreX - 10, centreY - 15, 30, 20);
}

void WidgetLidar::processTcpDatas(QString data)
{
    data.remove('\n');                                // enlève les retours à la ligne
    data.remove(' ');                                 // enlève les espaces

    QStringList liste = data.split(";"); // Qt::SkipEmptyParts);   // split le texte à chaque ";"

    for (int i = 0; i < 360 && i < liste.size(); i++)
        distancesLidar[i] = liste[i].toInt();         // texte en nombre entier et le met a la meme place que la valeur que je recois

    update();                                         // actualiser a chauqe fois pour
}