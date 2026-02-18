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
    LauncherManager(RobotControlData &Data);
    ~LauncherManager() = default;
    LauncherParam calcLaunch(double distance);

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
    
    void AddHoodAnglePoint();
    void AddFlywheelRPMPoint();
    void AddTimeOfFlightPoint();
    
    LauncherParam Calculate(frc::Pose2d current, frc::Pose2d target, frc::Translation2d velocity);

private:
    Launcher m_Launcher;
    double m_launcherRPM;
    double m_launcherAngle;
    double m_phaseDelay;
    double m_minDistance;
    double m_maxDistance;
    std::map<double, double> hoodAngleMap;
    std::map<double, double> flywheelRPMMap;
    std::map<double, double> timeOfFlightMap;

};