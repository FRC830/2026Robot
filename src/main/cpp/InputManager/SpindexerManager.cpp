#include "InputManager/SpindexerManager.h"

void SpindexerManager::ResetState(RobotControlData &robotControlData)
{
    robotControlData.spindexerOutput.RPM = 0;
}

void SpindexerManager::HandleInput(RobotControlData &robotControlData)
{
    if (robotControlData.spindexerInput.enableSpindexer && robotControlData.launcherOutput.launcherAtSpeed)
    {
        robotControlData.spindexerOutput.RPM = ratbot::Spindexer::DEFAULT_SPEED;
    }  
    else
    {
        robotControlData.spindexerOutput.RPM = 0;
    }
    m_Spindexer.RunSpindexer(robotControlData.spindexerOutput.RPM);

}