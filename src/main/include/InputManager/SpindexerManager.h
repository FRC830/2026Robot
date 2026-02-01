#pragma once

#include "HAL/SpindexerHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
#include <MechanismConfig.h>

class SpindexerManager
{
    public:
        SpindexerManager() = default;
        ~SpindexerManager() = default;

        void ResetState(RobotControlData &robotControlData);
        void HandleInput(RobotControlData &robotControlData);

    private:
        Spindexer m_Spindexer;
        double m_SpindexerRPM;

        
};