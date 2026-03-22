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
    m_data.states.Intaking = true;
    
}

bool intake::IsFinished()
{
    return m_timer.Get().value() > 3.0;
}

void intake::End(bool interrupted)
{
    m_data.states.Intaking = false;
    m_data.intakeInput.intakeDirection = 0;
}