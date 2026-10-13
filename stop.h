#ifndef STOP_H
#define STOP_H

#include "comportement.h"

class Stop : public Comportement
{
public:
    explicit Stop(std::array<int, 360> &distance, QObject *parent = nullptr);
public slots:
    void process() override;


};

#endif // STOP_H
