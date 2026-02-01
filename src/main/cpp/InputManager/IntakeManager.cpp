#include "InputManager/IntakeManager.h"

void IntakeManager::HandleInput(RobotControlData &robotControlData)
{
    if (robotControlData.intakeInput.intakeState)//true means up
    {
        m_intakeHAL.SequenceStore();
    }
    if (!robotControlData.intakeInput.intakeState)
    {
        m_intakeHAL.SequenceDown();
    }
    m_intakeHAL.RunIntake(robotControlData.intakeInput.intakeDirection);
}

void IntakeManager::ResetState()
{
    m_intakeHAL.SequenceStore();            
}