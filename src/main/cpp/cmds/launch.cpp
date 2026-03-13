#include <cmds/launch.h>
#include <MechanismConfig.h>


launch::launch(RobotControlData& data) : m_data(data)
{}

void launch::Initialize()
{
    m_data.launcherInput.disableLauncher = true;
    m_data.launcherInput.indexerSpeeds = 0;
    m_data.launcherInput.launcherRPM = 0;
    m_data.launcherInput.autoAim = false;
    m_timer.Start();
}

void launch::Execute()
{
    m_data.launcherInput.disableLauncher = false; //enable launcher and set to default values
    m_data.launcherInput.indexerSpeeds = 0.8;
    m_data.launcherInput.launcherRPM = -3000;
    m_data.launcherInput.autoAim = true;
}

bool launch::IsFinished()
{
    return m_timer.Get().value() > 8.0;
}