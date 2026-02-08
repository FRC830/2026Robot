#pragma once

#include <rev/SparkMax.h>
#include "CanConfig.h"
#include <frc/Servo.h>
#include <frc/Timer.h>

class LinearActuator{
    public:
        LinearActuator();
        ~LinearActuator() = default;
        
        void SetFirstHatchState(int dir);
        void SetSecondHatchState(int dir);
        void setPosition(double pos);
        void updateCurPos();
        double getPosition();
        bool isFinished();
        
    private:
        frc::Servo m_LinearActuator{LinActID};
        const double m_speed = 10; // max speed
        const double m_length = 10; // length of the actuator
        double lastTime = 0;
        double setPos;
        double curPos;
        frc::Timer m_timer;
};