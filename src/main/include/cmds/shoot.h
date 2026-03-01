#pragma once

#include <frc2/command/CommandHelper.h>
#include "RobotControlData.h"
#include <frc/Timer.h>

class shoot : public frc2::CommandHelper<frc2::Command, shoot>
{
public:
    explicit shoot(RobotControlData& data);
    ~shoot() = default;

    void Initialize() override;
    void Execute() override;
    bool IsFinished() override;
    void End(bool interrupted) override;

private:
    RobotControlData& m_data;
    int m_state;
    frc::Timer m_timer;
};