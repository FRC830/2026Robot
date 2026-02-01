#include "InputManager/SpindexerManager.h"

void SpindexerManager::ResetState(RobotControlData &robotControlData)
{
    robotControlData.spindexer.RPM = 0;
}

void SpindexerManager::HandleInput(RobotControlData &robotControlData)
{
    robotControlData.spindexer.RPM = ratbot::Spindexer::DEFAULT_SPEED + robotControlData.spindexer.joystick * 0.5;
    m_Spindexer.RunSpindexer(robotControlData.spindexer.RPM);
}