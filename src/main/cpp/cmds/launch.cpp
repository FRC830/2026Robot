// #include <cmds/launch.h>
// #include <MechanismConfig.h>


// launch::launch(RobotControlData& data) : m_data(data)
// {}

// void launch::Initialize()
// {
//     m_data.launcherInput.disableLauncher = true;
//     m_data.launcherInput.indexerSpeeds = 0;
//     m_data.launcherInput.launcherRPM = 0;
//     m_data.launcherInput.autoAim = false;
//     m_timer.Start();
// }

// void launch::Execute()
// {
//     m_data.launcherInput.autoAim = false;
//     m_data.launcherInput.disableLauncher = false;
//     m_data.launcherInput.launcherRPM = -4400;
//     m_data.launcherInput.indexerSpeeds = -2000;
// }

// bool launch::IsFinished()
// {
//     if m_timer.Get() > 
// }