#include "InputManager/LauncherManager.h"
#include <frc/DriverStation.h>

void LauncherManager::HandleInput(RobotControlData &robotControlData){
    
    if (robotControlData.launcherInput.disableLauncher){
        m_launcherRPM = 0;
    }
    else{
        m_launcherAngle = robotControlData.launcherInput.launcherAngle;
        m_launcherRPM = robotControlData.launcherInput.launcherRPM; //configure max speed
    }
    
    m_Launcher.SetRPM(m_launcherRPM);
    m_Launcher.SetAngle(m_launcherAngle);
    if (robotControlData.launcherInput.enableIndexer)
    {
        m_Launcher.SetIndexerSpeeds();
    }
    robotControlData.launcherOutput.leftLauncherRPM = m_Launcher.GetLeftLauncherRPM();
    robotControlData.launcherOutput.rightLauncherRPM = m_Launcher.GetRightLauncherRPM();
    robotControlData.launcherOutput.launcherAtSpeed = m_Launcher.AreFlywheelsAtDesiredSpeed();
    robotControlData.launcherOutput.launcherAngle = m_Launcher.GetAngle();
    frc::SmartDashboard::PutNumber("LeftLauncherRPM",m_Launcher.GetLeftLauncherRPM());
    frc::SmartDashboard::PutNumber("RightLauncherRPM",m_Launcher.GetRightLauncherRPM());
    frc::SmartDashboard::PutNumber("LauncherAngle",m_Launcher.GetAngle());
    
}

void LauncherManager::ResetState(){
    m_launcherRPM = 0.0;
    m_launcherAngle = 0.0;
}

LauncherManager::LauncherManager()
{
    m_launcherRPM = 0;
    //put some points here, for now placeholders
    double dist = 67;
    double angle = 67;
    double RPM = 67;
    double t = 67;


}