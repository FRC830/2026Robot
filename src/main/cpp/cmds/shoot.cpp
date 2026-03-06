#include <cmds/shoot.h>
#include <MechanismConfig.h>


shoot::shoot(RobotControlData& data) : m_data(data)
{}

void shoot::Initialize()
{
    m_data.launcherInput.disableLauncher = true;
    m_data.launcherInput.indexerSpeeds = 0;
    m_data.launcherInput.launcherSpeed = 0;
    m_data.launcherInput.autoAim = false;
    m_timer.Restart();

}

void shoot::Execute()
{
    m_data.launcherInput.autoAim = true;
    m_data.launcherInput.disableLauncher = false;
    m_data.spindexer.RPM = ratbot::Spindexer::DEFAULT_SPEED;
    // run launcher calc
}

bool shoot::IsFinished()
{
    units::second_t time = 10.0_s;
    return (m_timer.Get() >= time); // shoot for 10 seconds
}

void shoot::End(bool interrupted)
{
    m_timer.Stop();
}