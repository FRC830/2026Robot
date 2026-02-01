#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include "HAL/IntakeHAL.h"

class IntakeManager
{
    public:
        IntakeManager();
        ~IntakeManager() = default;
        
        void ResetState();
        void HandleInput(RobotControlData &robotControlData);

    private:
        IntakeHAL m_intakeHAL;
        int intakeRollerDirection;
};