#include "stop.h"

Stop::Stop(std::array<int, 360> &distance, QObject *parent)
    : Comportement{distance, parent}
{}

void Stop::process()
{

    emit deplacer(0,0);
}
