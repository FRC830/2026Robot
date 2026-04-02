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
    controlData.states.Intaking = true;
    controlData.states.Passing = false; // Ensure Passing is false when Launching is toggled
    controlData.states.Jam = false; // Ensure Jam is false when Launching is toggled
    controlData.states.Launching = false; // Ensure Launching is false when Passing is toggled
    controlData.states.Defense = false; // Ensure Defense is false when Intaking is toggled
}

bool intake::IsFinished()
{
    return m_timer.Get().value() > 0.3;
}

void intake::End(bool interrupted)
{

}
