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
}

void shoot::Execute()
{
    m_data.launcherInput.autoAim = true;
}

bool shoot::IsFinished()
{
    
}