#include "HAL/IntakeHAL.h"
#include <frc/smartdashboard/SmartDashboard.h>

// contructor: set the zero position of the encoder to the current value
// abosulte encoder stuff below gets re

// m_zeroPos = encoder.Get()
IntakeHAL::IntakeHAL()
{
    m_zeroPos = encoder.Get();
    
    frc::SmartDashboard::PutNumber("IntakeAngle", encoder.Get());

}

double IntakeHAL::GetIntakeAngle()
{
    return encoder.Get() - m_zeroPos;
}

void IntakeHAL::RunIntake(int direction)
{
    m_rollerMotor.Set(-direction * ratbot::Intake::INTAKE_ROLLER_SPEED);
}
void IntakeHAL::MoveIntake(int direction)
{
    m_angleMotor.Set(direction * ratbot::Intake::INTAKE_ANGLE_SPEED);
}

void IntakeHAL::SequenceDown()
{
    if (encoder.Get() < ratbot::Intake::DOWN_LOCATION + deadzone)
    {
        MoveIntake(1);
    }
    else
    {
        MoveIntake(0);
    }
}

void IntakeHAL::SequenceStore()
{
    if (encoder.Get() > m_zeroPos + deadzone)
    {
        MoveIntake(-1);
    }
    else
    {
        MoveIntake(0);
    }
}