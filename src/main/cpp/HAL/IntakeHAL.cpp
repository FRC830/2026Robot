#include "HAL/IntakeHAL.h"

void IntakeHAL::RunIntake(int direction)
{
    m_rollerMotor.Set(direction * ratbot::Intake::INTAKE_ROLLER_SPEED);
}
void IntakeHAL::MoveIntake(double setpoint)
{
    m_thetaPID.SetTolerance(5, 10);
    m_thetaPID.SetIntegratorRange(-0.5, 0.5);
    //std::clamp(m_thetaPID.Calculate(m_angleMotor.GetAbsoluteEncoder().GetPosition(), setpoint), -0.5, 0.5);
    m_angleMotor.Set(m_thetaPID.Calculate(m_angleMotor.GetAbsoluteEncoder().GetPosition(),setpoint*ratbot::Intake::GEAR_RATIO));
}

void IntakeHAL::SequenceDown()
{
    MoveIntake(ratbot::Intake::DEPLOYED_LOCATION);

}
void IntakeHAL::SequenceStore()
{
    MoveIntake(ratbot::Intake::STORED_LOCATION);

}
void IntakeHAL::ResetPID()
{
    m_thetaPID.Reset();
}