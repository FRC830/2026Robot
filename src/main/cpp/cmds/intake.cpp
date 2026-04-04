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
    m_data.states.Passing = false; // Ensure Passing is false when Launching is toggled
    m_data.states.Jam = false; // Ensure Jam is false when Launching is toggled
    m_data.states.Launching = false; // Ensure Launching is false when Passing is toggled
    m_data.states.Defense = false; // Ensure Defense is false when Intaking is toggled
    m_data.intakeInput.intakeDirection = 1.0;
}

bool intake::IsFinished()
{
    return m_timer.Get().value() > 0.3;
}

void intake::End(bool interrupted)
{

}
