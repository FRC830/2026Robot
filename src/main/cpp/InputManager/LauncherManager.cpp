#include "InputManager/LauncherManager.h"

void LauncherManager::HandleInput(RobotControlData &robotControlData){
    
    if (false){
        ResetState();
    }
    else{
        m_launcherAngle = robotControlData.launcherInput.launcherAngle;
        m_launcherRPM = robotControlData.launcherInput.launcherRPM; //configure max speed
    }
    
    m_Launcher.SetRPM(m_launcherRPM);
    m_Launcher.SetAngle(m_launcherAngle);
    m_Launcher.SetIndexerSpeeds(robotControlData.launcherInput.indexerSpeeds);
    robotControlData.launcherOutput.leftLauncherRPM = m_Launcher.GetLeftLauncherRPM();
    robotControlData.launcherOutput.rightLauncherRPM = m_Launcher.GetRightLauncherRPM();
    robotControlData.launcherOutput.launcherAtSpeed = m_Launcher.AreFlywheelsAtDesiredSpeed();
    robotControlData.launcherOutput.launcherAngle = m_Launcher.GetAngle();
    frc::SmartDashboard::PutNumber("LeftLauncherRPM",m_Launcher.GetLeftLauncherRPM());
    frc::SmartDashboard::PutNumber("RightLauncherRPM",m_Launcher.GetRightLauncherRPM());
    frc::SmartDashboard::PutNumber("LauncherAngle",m_Launcher.GetAngle());
    
}
/*
LauncherParam calcLaunch(double distance){
    if(distance > map1 && distance < map2){

        return LauncherParam{theta1,rpm1};
    }
    else if (distance > map2 && distance < map3)
    {
        return LauncherParam{theta2,rpm2};
    }
    else
    
}
*/
void LauncherManager::ResetState(){
    m_launcherRPM = 0.0;
    m_launcherAngle = 0.0;
}

