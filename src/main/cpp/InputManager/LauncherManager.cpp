#include "InputManager/LauncherManager.h"

void LauncherManager::HandleInput(RobotControlData &robotControlData){
    if (robotControlData.launcherInput.disableLauncher){
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

LauncherParam LauncherManager::Calculate(frc::Pose2d current, frc::Pose2d target, frc::Translation2d velocity)
{
    LauncherParam calc;
    
    //frc::Twist2d(velocity.X()*m_phaseDelay, velocity.Y()*m_phaseDelay, velocity.Angle()*m_phaseDelay);

    // for(int i; i<6; i++){
    //     calc.timeOfFlight = timeOfFlightMap.
    // }
    return calc;
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

LauncherManager::LauncherManager(RobotControlData &Data)
{
    m_launcherRPM = 1000;
    //put some points here
    hoodAngleMap.insert({'point','angle'});
    flywheelRPMMap.insert({'point','rpm'});
    timeOfFlightMap.insert({'point','TOF'});

}