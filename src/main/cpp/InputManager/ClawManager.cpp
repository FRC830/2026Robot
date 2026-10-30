#include "InputManager/ClawManager.h"

void ClawManager::HandleInput(RobotControlData &robotControlData) {
    //SetClawLevel
        m_Claw.ClawIntake(robotControlData.clawInput.ClawState)
    
}

void ClawManager::ResetState() {
    m_Claw.ClawIntake(0);
}