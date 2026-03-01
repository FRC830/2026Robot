#include "HAL/IntakeHAL.h"
#include <frc/smartdashboard/SmartDashboard.h>
void IntakeHAL::RunIntake(int direction)
{
    m_rollerMotor->Set(direction * ratbot::Intake::INTAKE_ROLLER_SPEED);
}
void IntakeHAL::MoveIntake(int direction)
{
    m_angleMotor.Set(direction * ratbot::Intake::INTAKE_ANGLE_SPEED);
    frc::SmartDashboard::PutNumber("IntakeAngle", m_angleMotor.GetAbsoluteEncoder().GetPosition());
}

void IntakeHAL::SequenceDown()
{
    if (m_angleMotor.GetAbsoluteEncoder().GetPosition() < ratbot::Intake::DOWN_LOCATION + deadzone)
    {
        MoveIntake(-1);
    }
    else
    {
        MoveIntake(0);
    }
}

void IntakeHAL::SequenceStore()
{
    if (m_angleMotor.GetAbsoluteEncoder().GetPosition() > 0 + deadzone)
    {
        MoveIntake(1);
    }
    else
    {
        MoveIntake(0);
    }
}
