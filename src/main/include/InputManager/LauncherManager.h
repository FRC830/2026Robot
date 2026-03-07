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

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
    

    
    LauncherParam Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY);

    // Return a pointer to the internal Launcher instance so other subsystems
    // can use the same hardware controller instead of creating their own.
    Launcher* GetLauncher() { return &m_Launcher; }

private:
    Launcher m_Launcher;
    double m_launcherRPM;
    double m_launcherAngle;
    double m_phaseDelay;
    double m_minDistance;
    double m_maxDistance;
    
    wpi::interpolating_map<double, double> hoodAngleMap;
    wpi::interpolating_map<double, double> flywheelRPMMap;
    wpi::interpolating_map<double, double> timeOfFlightMap;


    
};