#include <cmds/launch.h>
#include <MechanismConfig.h>


launch::launch(RobotControlData& data) : m_data(data)
{}

void launch::Initialize()
{
    m_data.launcherInput.disableLauncher = true;
    m_data.launcherInput.indexerSpeeds = 0;
    m_data.launcherInput.autoAim = false;
    m_timer.Restart();
}

void launch::Execute()
{
    m_data.launcherInput.launcherRPM = -3000;
    m_data.states.Passing = true;
}

bool launch::IsFinished()
{
    return m_timer.Get().value() > 8.0;
}

void launch::End(bool interrupted)
{

    m_data.launcherInput.disableLauncher = true; //disable launcher
    m_data.launcherInput.indexerSpeeds = 0;
    m_data.launcherInput.autoAim = false;
    m_data.states.Passing = false;
}