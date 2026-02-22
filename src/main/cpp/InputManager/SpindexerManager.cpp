#include "InputManager/SpindexerManager.h"

void SpindexerManager::ResetState(RobotControlData &robotControlData)
{
    robotControlData.spindexerOutput.RPM = 0;
}

void SpindexerManager::HandleInput(RobotControlData &robotControlData)
{
    if (robotControlData.spindexerInput.enableSpindexer)
    {
        robotControlData.spindexerOutput.RPM = ratbot::Spindexer::DEFAULT_SPEED;
        m_Spindexer.RunSpindexer(robotControlData.spindexerOutput.RPM);
    }  
    else
    {
        robotControlData.spindexerOutput.RPM = 0;
        m_Spindexer.RunSpindexer(robotControlData.spindexerOutput.RPM);
    }
}