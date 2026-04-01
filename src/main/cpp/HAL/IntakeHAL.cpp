#include "HAL/IntakeHAL.h"
#include <frc/smartdashboard/SmartDashboard.h>

// contructor: set the zero position of the encoder to the current value
// abosulte encoder stuff below gets re

// m_zeroPos = encoder.Get()


double IntakeHAL::GetIntakeAngle()
{
    return encoder.Get();

}

void IntakeHAL::RunIntake(int direction)
{
    m_rollerMotor.Set(-direction * ratbot::Intake::INTAKE_ROLLER_SPEED);

    frc::SmartDashboard::PutNumber("IntakeAngle", encoder.Get());

}
void IntakeHAL::MoveIntake(double direction)
{
    m_angleMotor.Set(direction * ratbot::Intake::INTAKE_ANGLE_SPEED);
}

void IntakeHAL::SequenceDown()
{
    if (encoder.Get() < ratbot::Intake::DOWN_LOCATION + deadzone)
    {
        MoveIntake(-0.3);
    }
    else
    {
        MoveIntake(0);
    }
}

void IntakeHAL::ToPosition(double pos)
{
    if(pos>encoder.Get()){
         if (encoder.Get() < ratbot::Intake::DOWN_LOCATION + deadzone)
        {
            MoveIntake(-0.3);
        }
        else
        {
            MoveIntake(0);
        }
    }
    else
    {
        if (encoder.Get() > ratbot::Intake::UP_LOCATION + deadzone)
        {
            MoveIntake(1);
        }
        else
        {
            MoveIntake(0);
        }
    }
    
}

void IntakeHAL::SequenceStore()
{
    if (encoder.Get() > ratbot::Intake::UP_LOCATION + deadzone)
    {
        MoveIntake(1);
    }
    else
    {
        MoveIntake(0);
    }
}