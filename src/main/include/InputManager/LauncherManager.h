#pragma once

#include "HAL/LauncherHAL.h"
#include "RobotControlData.h"
#include <frc/DigitalInput.h>


class LauncherManager
{
public:
    LauncherManager() = default;
    ~LauncherManager() = default;

    void ResetState();
    void HandleInput(RobotControlData &robotControlData);
private:
    Launcher m_Launcher;
    bool m_setLauncherToSpeed = false;
    bool m_setLauncherToZero = false;
};