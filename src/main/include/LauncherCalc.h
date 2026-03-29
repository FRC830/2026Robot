#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
#include <wpi/interpolating_map.h>


class LauncherCalc
{
public:
    LauncherCalc();
    ~LauncherCalc() = default;
    
    double Calculate(double distance, frc::Pose2d current, double velocityX, double velocityY);

    // Return a pointer to the internal Launcher instance so other subsystems
    // can use the same hardware controller instead of creating their own.
    //Launcher* GetLauncher() { return &m_Launcher; }

private:
    wpi::interpolating_map<double, double> flywheelRPMMap;



    
};