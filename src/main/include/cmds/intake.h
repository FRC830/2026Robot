#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class intake : public frc2::CommandHelper<frc2::Command, intake>
{
public:
    intake(RobotControlData& data);
    ~intake() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
    frc::Timer m_timer;
};