#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
#include <wpi/interpolating_map.h>

struct LauncherParam{
    double hoodAngle;
    double flywheelRPM;
    double aimAngleRad;
    double timeOfFlight;
    bool inRange;
};
class LauncherManager
{
public:
    LauncherManager();
    ~LauncherManager() = default;
    LauncherParam calcLaunch(double distance);

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
    
    void AddHoodAnglePoint();
    void AddFlywheelRPMPoint();
    void AddTimeOfFlightPoint();
    
    LauncherParam Calculate(double distance, frc::Pose2d current, frc::Translation2d velocity);

private:
    Launcher m_Launcher;
    double m_launcherRPM = 1000;
    double m_launcherAngle;
    double m_phaseDelay;
    double m_minDistance;
    double m_maxDistance;
    
    wpi::interpolating_map<double, double> hoodAngleMap;
    wpi::interpolating_map<double, double> flywheelRPMMap;
    wpi::interpolating_map<double, double> timeOfFlightMap;
    
};