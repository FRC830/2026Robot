#include "InputManager/LauncherManager.h"


void LauncherManager::HandleInput(RobotControlData &robotControlData){
    if(robotControlData.launcherInput.setLauncherToSpeed){
        m_setLauncherToSpeed = true;
        m_setLauncherToZero = false;
    }else if (robotControlData.launcherInput.disableLauncher){
        m_setLauncherToSpeed = false;
        m_setLauncherToZero = true;
    }

    if(m_setLauncherToSpeed){
        m_Launcher.SetLauncherSpeeds(500.0, -500.0); //configure speeds
    }
    if(m_setLauncherToZero){
        m_Launcher.SetLauncherSpeeds(0.0,0.0);
    }
    m_Launcher.SetIndexerSpeeds(robotControlData.launcherInput.indexerSpeeds);
    // if(m_Launcher.BeamBreakStatus()){
    //     m_Launcher.SetWheelSpeeds(0,0);
    // }
    robotControlData.launcherOutput.leftSpeed = m_Launcher.GetLeftLauncherSpeed();
    robotControlData.launcherOutput.rightSpeed = m_Launcher.GetRightLauncherSpeed();
    robotControlData.launcherOutput.launcherAtSpeed = m_Launcher.AreFlywheelsAtDesiredSpeed();
}

void LauncherManager:: ResetState(){
    m_setLauncherToSpeed = false;
    m_setLauncherToZero = true;
}