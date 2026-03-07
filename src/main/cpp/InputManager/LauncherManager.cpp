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
    m_Launcher.SetIndexerSpeeds(robotControlData.launcherInput.indexerSpeeds);
    robotControlData.launcherOutput.leftLauncherRPM = m_Launcher.GetLeftLauncherRPM();
    robotControlData.launcherOutput.rightLauncherRPM = m_Launcher.GetRightLauncherRPM();
    robotControlData.launcherOutput.launcherAtSpeed = m_Launcher.AreFlywheelsAtDesiredSpeed();
    robotControlData.launcherOutput.launcherAngle = m_Launcher.GetAngle();
    frc::SmartDashboard::PutNumber("LeftLauncherRPM",m_Launcher.GetLeftLauncherRPM());
    frc::SmartDashboard::PutNumber("RightLauncherRPM",m_Launcher.GetRightLauncherRPM());
    frc::SmartDashboard::PutNumber("LauncherAngle",m_Launcher.GetAngle());
    
}

LauncherParam LauncherManager::Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY)
{
    LauncherParam calc;
    
    double timeOfFlight;
    double hoodAngle;
    double flywheelRPM;
    double aimAngle;
    frc::Pose2d lookaheadPose;
    double lookaheadLauncherToTargetDistance = distance;
    frc::Translation2d targetPosition;

    for(int i = 0; i<6; i++){
        timeOfFlight = timeOfFlightMap.operator[](distance);
        double offsetX = velocityX * calc.timeOfFlight;
        double offsetY = velocityY * calc.timeOfFlight;
        //lookaheadPose = frc::Pose2d(current.Translation().operator+(frc::Translation2d(units::meter_t(offsetX),units::meter_t(offsetY))), current.Rotation());

        bool blueAlliance = frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue;

        //double x = lookaheadPose.X().value();
        //double y = lookaheadPose.Y().value();
        
        double x = current.X().value();
        double y = current.Y().value();

        if (blueAlliance)
        {
            double targetangle = atan2(4.035 - y,4.626 - x);
            targetPosition = frc::Translation2d( units::length::meter_t(4.626 - x),units::length::meter_t(4.035 - y));
        }
        else
        {
            double targetangle = atan2(4.035 - y, 11.915 - x);
            targetPosition= frc::Translation2d(units::length::meter_t(11.915 - x),units::length::meter_t(4.035 - y));
        }
            
        lookaheadLauncherToTargetDistance = targetPosition.Norm().value();
    }
    //aimAngle = atan2(targetPosition.Y().value()-lookaheadPose.Y().value(), targetPosition.X().value()-lookaheadPose.X().value());
    aimAngle = atan2(targetPosition.Y().value()-current.Y().value(), targetPosition.X().value()-current.X().value());
    flywheelRPM = flywheelRPMMap.operator[](distance);
    hoodAngle = hoodAngleMap.operator[](distance);

    calc.flywheelRPM = flywheelRPM;
    calc.hoodAngle = hoodAngle;
    calc.aimAngleRad = aimAngle;
    calc.timeOfFlight = timeOfFlight;
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

LauncherManager::LauncherManager()
{
    m_launcherRPM = 0;
    //put some points here, for now placeholders


    hoodAngleMap.insert(1,1);
    hoodAngleMap.insert(2,2);
    hoodAngleMap.insert(3,3);
    flywheelRPMMap.insert(1, 1);
    flywheelRPMMap.insert(2, 2);
    flywheelRPMMap.insert(3, 3);
    timeOfFlightMap.insert(1, 1);
    timeOfFlightMap.insert(2, 2);
    timeOfFlightMap.insert(3, 3);


}