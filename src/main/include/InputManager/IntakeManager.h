#pragma once

#include "RobotControlData.h"
#include "CanConfig.h"
#include "HAL/IntakeHAL.h"
#include <frc/Timer.h>

class IntakeManager
{
    public:
        IntakeManager() = default;
        ~IntakeManager() = default;
        
        void ResetState();
        void HandleInput(RobotControlData &robotControlData);
        void Shake(RobotControlData &robotControlData);
    private:
        IntakeHAL m_intakeHAL;
        int intakeRollerDirection;
        int switchCaseState = 0;
        frc::Timer m_Timer;
};
