#ifndef SERVO_H
#define SERVO_H

class Servo
{
public:
    Servo(float _offset_ms, float _amplitude_ms);

    float offset_ms;
    float amplitude_ms;

    void initialisation();
    void position(double angle);
};

#endif // SERVO_H