#ifndef COMPORTEMENT_H
#define COMPORTEMENT_H

#include <QObject>
#include <array>
class Comportement : public QObject
{
    Q_OBJECT
public:
    explicit Comportement(std::array<int, 360> &distances, QObject *parent = nullptr);
protected:
    std::array<int, 360> &distancesLidar;
public slots:
    virtual void process();
signals:
    void deplacer(double vitesse, double angle);
};

#endif // COMPORTEMENT_H
