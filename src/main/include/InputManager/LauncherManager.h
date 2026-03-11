#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>
#include <wpi/interpolating_map.h>

class LauncherManager
{
public:
    LauncherManager();
    ~LauncherManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);

private:
    Launcher m_Launcher;
    double m_launcherRPM = 1000;
    double m_launcherAngle;
    double m_phaseDelay;
    double m_minDistance;
    double m_maxDistance;
};