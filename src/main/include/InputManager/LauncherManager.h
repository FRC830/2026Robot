#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>

class LauncherManager
{
public:
    LauncherManager();
    ~LauncherManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
    
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
    


    
};