#include "InputManager/LauncherManager.h"


void LauncherManager::HandleInput(RobotControlData &robotControlData){
    if (robotControlData.launcherInput.disableLauncher){
        m_launcherSpeed = 0.0;
    }
    else{
        m_launcherSpeed = robotControlData.launcherInput.launcherSpeed; //configure max speed
    }
    m_Launcher.SetLauncherSpeeds(m_launcherSpeed, -m_launcherSpeed);
    m_Launcher.SetIndexerSpeeds(robotControlData.launcherInput.indexerSpeeds);
    // if(m_Launcher.BeamBreakStatus()){
    //     m_Launcher.SetWheelSpeeds(0,0);
    // }
    robotControlData.launcherOutput.leftSpeed = m_Launcher.GetLeftLauncherSpeed();
    robotControlData.launcherOutput.rightSpeed = m_Launcher.GetRightLauncherSpeed();
    robotControlData.launcherOutput.launcherAtSpeed = m_Launcher.AreFlywheelsAtDesiredSpeed();
}

void LauncherManager:: ResetState(){
    m_launcherSpeed = 0.0;
}