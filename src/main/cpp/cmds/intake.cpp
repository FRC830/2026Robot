#include <cmds/intake.h>
#include <MechanismConfig.h>


intake::intake(RobotControlData& data) : m_data(data)
{}

void intake::Initialize()
{
    m_timer.Restart();
}

void intake::Execute()
{
    m_data.intakeInput.intakeDirection = 1.0;
    m_data.intakeInput.intakeState = false;
}

bool intake::IsFinished()
{
    return m_timer.Get().value() > 0.3;
}

void intake::End(bool interrupted)
{

}