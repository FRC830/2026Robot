#pragma once

#include "HAL/SpindexerHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
#include <MechanismConfig.h>
#include <frc/Timer.h>

class SpindexerManager
{
    public:
        SpindexerManager() = default;
        ~SpindexerManager() = default;

        void ResetState(RobotControlData &robotControlData);
        void HandleInput(RobotControlData &robotControlData);

    private:
        int state = 0;
        Spindexer m_Spindexer;
        double m_SpindexerRPM;
        frc::Timer m_Timer;
        
};