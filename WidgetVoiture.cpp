#include "WidgetVoiture.h"
#include <QPainter>
#include <QPen>
#include <QStringList>

WidgetVoiture::WidgetVoiture(QWidget *parent)
    : QWidget{parent}
{
    vitesse = 0.0;
    angle = 0.0;
    setMinimumSize(200, 200);
}

void WidgetVoiture::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QPen pen;

    // Cadre qu'on a fait dans le TD
    pen.setWidth(4);
    pen.setColor(QColor(255, 0, 0));
    painter.setBrush(QColor(0, 220, 220));
    painter.setPen(pen);
    painter.drawRect(10, 10, width() - 20, height() - 20);

    // Affichage de la vitesse et de l'angle
    pen.setWidth(1);
    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen);
    painter.drawText(25, 35, "Vitesse : " + QString::number(vitesse, 'f', 2));
    painter.drawText(25, 55, "Angle : " + QString::number(angle, 'f', 2));

    // La voiture au centre
    painter.translate(width() / 2, height() / 2);

    // Corps de la voiture
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 200, 0));
    painter.drawRect(-30, -60, 60, 120);

    // Roues
    painter.setBrush(QColor(0, 0, 0));
    const double angleTOURNER = angle * 30.0; //
    // pas toutes les roues doivent tourner c que les Roues en avant qui tournent et qui sont en arriere doivent etre fixent
    painter.drawRect(-38, 20, 8, 25);   // arrière gauche
    painter.drawRect(30, 20, 8, 25);    // arrière droite

    // Roue avant gauche
    painter.save();
    painter.translate(-34, -32.5);
    painter.rotate(angleTOURNER);
    painter.drawRect(-4, -12, 8, 25);
    painter.restore();

    // Roue avant droite
    painter.save();
    painter.translate(34, -32.5);
    painter.rotate(angleTOURNER);
    painter.drawRect(-4, -12, 8, 25);
    painter.restore();

    // Triangle indiquant le sens d'avant
    QPolygon triangleSens;
    triangleSens << QPoint(0, -15) << QPoint(-10, 5) << QPoint(10, 5);
    painter.setBrush(QColor(255, 255, 0));
    painter.drawPolygon(triangleSens);
}
void WidgetVoiture::processTcpDatas(QString data)
{
    // notre but maintenant c d'avoir des donnees sous forme de texte "-1,1" que l'on tranasforme en vitesse=-1 et angle=1(par ex)
    // Séparation "vitesse;angle"
    QStringList parts = data.trimmed().split(';');//pour
    if (parts.size() < 2)
        return;

    // Conversion et limitation des valeurs dans l'intervalle [-1; 1]
    vitesse = qBound(-1.0, parts[0].toDouble(), 1.0);
    angle   = qBound(-1.0, parts[1].toDouble(), 1.0);

    update();
}
