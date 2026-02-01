#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"

#include "HAL/IntakeHAL.h"
class IntakeHAL
{
    public:
        IntakeHAL();
        ~IntakeHAL() = default;
        bool toggle = false;
        
};