#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class launch : public frc2::CommandHelper<frc2::Command, launch>
{
public:
    explicit launch(RobotControlData& data);
    ~launch() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
    int m_state;
    frc::Timer m_timer;
};