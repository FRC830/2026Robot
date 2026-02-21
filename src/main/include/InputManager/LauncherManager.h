#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
struct LauncherParam{
    double launcherAngle;
    double launcherRPM;
};
class LauncherManager
{
public:
    LauncherManager() = default;
    ~LauncherManager() = default;
    LauncherParam calcLaunch(double distance);

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    Launcher m_Launcher;
    double m_launcherRPM = 1000;
    double m_launcherAngle;
};