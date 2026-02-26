#include "InputManager/SpindexerManager.h"

void SpindexerManager::ResetState(RobotControlData &robotControlData)
{
    robotControlData.spindexer.RPM = 0;
}

void SpindexerManager::HandleInput(RobotControlData &robotControlData)
{
    robotControlData.spindexer.RPM = ratbot::Spindexer::DEFAULT_SPEED;
    m_Spindexer.RunSpindexer(robotControlData.spindexer.RPM, robotControlData.launcherOutput.launcherAtSpeed);
}