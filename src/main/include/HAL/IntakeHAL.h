#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include <rev/SparkMax.h>

class Intake 
{
    public:
        Intake();
        ~Intake() = default;

        void IntakeOn();
        void IntakeOff();
        void MoveUp();
};
