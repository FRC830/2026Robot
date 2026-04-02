#include <cmds/launch.h>
#include <MechanismConfig.h>


launch::launch(RobotControlData& data) : m_data(data)
{}

void launch::Initialize()
{
    m_data.states.Launching = false;
    m_data.states.Passing = false; // Ensure Passing is false when Launching is toggled
    m_data.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
    m_data.states.Jam = false; // Ensure Jam is false when Launching is toggled
    m_data.states.Defense = false; // Ensure Defense is false when Intaking is toggled
    m_timer.Restart();
}

void launch::Execute()
{
    m_data.states.Launching = true;
    m_data.states.Passing = false; // Ensure Passing is false when Launching is toggled
    m_data.states.Intaking = false; // Ensure Intaking is false when Launching is toggled
    m_data.states.Jam = false; // Ensure Jam is false when Launching is toggled
    m_data.states.Defense = false; // Ensure Defense is false when Intaking is toggled
}

bool launch::IsFinished()
{
    return m_timer.Get().value() > 8.0;
}

void launch::End(bool interrupted)
{

    m_data.launcherInput.disableLauncher = true; //disable launcher
    m_data.launcherInput.states.Launching = false;
}
