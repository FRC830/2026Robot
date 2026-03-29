#include "InputManager/IntakeManager.h"
#include <frc/smartdashboard/SmartDashboard.h>

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
    frc::SmartDashboard::PutNumber("IntakeAngle", m_intakeHAL.GetIntakeAngle());
}

void IntakeManager::Shake(RobotControlData &robotControlData)
{
    switch (switchCaseState) {
        case 0:
        {
            m_Timer.Reset();
            m_Timer.Start();
            switchCaseState = 1;
            break;
        }
        case 1:
        {
            m_intakeHAL.SequenceDown();
            if(m_Timer.Get() > (units::time::second_t) 1) {
                switchCaseState = 2;
                break;
            }
        }
        case 2:
        {
            m_Timer.Reset();
            m_Timer.Start();
            switchCaseState = 3;
            break;
        }
        case 3:
        {
            m_intakeHAL.SequenceStore();
            if(m_Timer.Get() > (units::time::second_t) 1) {
                switchCaseState = 0;
                break;
            }
        }
        default: {
            break;
        }
    }
}

void IntakeManager::ResetState()
{
    m_intakeHAL.SequenceStore();            
}